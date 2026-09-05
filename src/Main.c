#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/Random.h"

#define STARS_MAX_DIST  500.0f
#define STARS_MAX       25000

Vec3 pos;
float speed;
float angle_y;
float angle_x;
Vector stars;

Vec3 World_Camera(const Vec3* const cam,const Vec3* const p){
    const float ox = p->x - cam->x;
    const float oy = p->y - cam->y;
    const float oz = p->z - cam->z;

    const float cyaw = cosf(angle_y);
    const float syaw = sinf(angle_y);

    const float cpitch = cosf(angle_x);
    const float spitch = sinf(angle_x);

    const float x1 = ox * cyaw + oz * syaw;
    const float z1 = -ox * syaw + oz * cyaw;

    const float y2 = oy * cpitch + z1 * spitch;
    const float z2 = -oy * spitch + z1 * cpitch;

    return (Vec3){
        .x = x1,
        .y = y2,
        .z = z2
    };
}
char World_Screen_Visible(const Vec3* const cam,const Vec3* const p){
    const Vec3 cp = World_Camera(cam, p);
    return cp.z > 0.001f;
}
Vec2 World_Screen(const Vec3* const cam,const Vec3* const p){
    const Vec3 cp = World_Camera(cam, p);

    if(cp.z <= 0.001f){
        return (Vec2){
			.x = 0.0f,
			.y = 0.0f
        };
    }

    const float wx = cp.x / cp.z;
    const float wy = cp.y / cp.z;

    const float sx = (wx + 1.0f) * 0.5f * (float)GetWidth();
    const float sy = (1.0f - wy) * 0.5f * (float)GetHeight();

    return (Vec2){
        .x = sx,
        .y = sy
    };
}

void Setup(AlxWindow* w){
    pos = (Vec3){
        .x = 0.0f,
        .y = 0.0f,
        .z = 0.0f
    };

    speed = 1.0f;
    angle_y = 0.0f; // YAW
    angle_x = 0.0f; // PITCH

    stars = Vector_New(sizeof(Vec3));
}
void Update(AlxWindow* w){
    const Vec3 pre = pos;
    const float dt = w->ElapsedTime;

    if(Stroke(ALX_KEY_UP).DOWN)
        angle_x -= F32_PI * dt;

    if(Stroke(ALX_KEY_DOWN).DOWN)
        angle_x += F32_PI * dt;

    if(Stroke(ALX_KEY_LEFT).DOWN)
        angle_y += F32_PI * dt;

    if(Stroke(ALX_KEY_RIGHT).DOWN)
        angle_y -= F32_PI * dt;


    const float pitch_limit = F32_PI * 0.5f - 0.001f;
    if(angle_x > pitch_limit)  angle_x = pitch_limit;
    if(angle_x < -pitch_limit) angle_x = -pitch_limit;


    if(Stroke(ALX_KEY_W).DOWN) speed *= 1.01f;
    if(Stroke(ALX_KEY_S).DOWN) speed *= 0.99f;
    
	//const float forward_x = sinf(angle_y);
    //const float forward_z = cosf(angle_y);
    //pos.x += forward_x * speed * dt;
    //pos.z += forward_z * speed * dt;
    //if(Stroke(ALX_KEY_R).DOWN) pos.y -= 1.0f * dt;
    //if(Stroke(ALX_KEY_F).DOWN) pos.y += 1.0f * dt;
	
	//const float cp = cosf(angle_x);
	//const float sp = sinf(angle_x);
	//const float cy = cosf(angle_y);
	//const float sy = sinf(angle_y);
	//const float look_x = sy * cp;
	//const float look_y = -sp;
	//const float look_z = cy * cp;
	//pos.x += speed * look_x * dt;
	//pos.y += speed * look_y * dt;
	//pos.z += speed * look_z * dt;
	
	pos.z += speed * dt;


    Clear(BLACK);

    for(int i = 0; i < stars.size; i++){
        const Vec3* const p = (Vec3*)Vector_Get(&stars, i);
        const Vec3 diff = Vec3_Sub(*p, pos);

        if(Vec3_Dot(diff, diff) > STARS_MAX_DIST * STARS_MAX_DIST){
			Vector_Remove(&stars, i);
			i--;
			continue;
        }

        if(World_Screen_Visible(&pos, p) && World_Screen_Visible(&pre, p)){
			const Vec2 pre_p = World_Screen(&pre,p);
			const Vec2 pos_p = World_Screen(&pos,p);
			Line_RenderX(WINDOW_STD_ARGS,pre_p,pos_p,WHITE,1.0f);
			//Circle_RenderX(WINDOW_STD_ARGS,pos_p,1.0f,WHITE);
        }
    }

    for(int i = stars.size;i < STARS_MAX;i++){
        const float az = Random_f64_MinMax(0.0f,F32_PI2);
        const float ay = Random_f64_MinMax(0.0f,F32_PI2);
        const float r = Random_f64_MinMax(0.0f,STARS_MAX_DIST);

        const float x = cosf(az) * sinf(ay) * r + pos.x;
        const float y = sinf(az) * r + pos.y;
        const float z = cosf(ay) * r + pos.z;

        Vector_Push(&stars,(Vec3[]){{
			.x = x,
			.y = y,
			.z = z
		}});
    }
}
void Delete(AlxWindow* w){
    Vector_Free(&stars);
}

int main(){
    if(Create(
        "Star Field",
        1920,
        1080,
        1,
        1,
        Setup,
        Update,
        Delete
    ))
        Start();

    return 0;
}