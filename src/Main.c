#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"

#define STARS_MAX	25000

float speed;
Vector stars;

Vec2 World_Screen(Vec3 p){
	const float wx = p.x / p.z;
	const float wy = p.y / p.z;
	const float sx = (wx + 1.0f) * 0.5f * (float)GetWidth();
	const float sy = (wy + 1.0f) * 0.5f * (float)GetHeight();
	return (Vec2){ sx,sy };
}

void Setup(AlxWindow* w){
	speed = 1.0f;
    stars = Vector_New(sizeof(Vec3));
}
void Update(AlxWindow* w){
    if(Stroke(ALX_KEY_W).DOWN){
		speed *= 1.01f;
	}
	if(Stroke(ALX_KEY_S).DOWN){
		speed *= 0.99f;
	}
	
	Clear(BLACK);

	for(int i = 0;i<stars.size;i++){
		Vec3* p = (Vec3*)Vector_Get(&stars,i);
		const Vec2 pp = World_Screen(*p);

		p->z -= speed * w->ElapsedTime;
		if(p->z < 0.01f){
			Vector_Remove(&stars,i);
			i--;
			continue;
		}

		const Vec2 ap = World_Screen(*p);
		Line_RenderX(WINDOW_STD_ARGS,pp,ap,WHITE,1.0f);
		//Circle_RenderX(WINDOW_STD_ARGS,World_Screen(*p),1.0f,WHITE);
	}


	for(int i = stars.size;i<STARS_MAX;i++){
		Vector_Push(&stars,(Vec3[]){{
			.x = Random_f64_MinMax(-10.0f,10.0f),
			.y = Random_f64_MinMax(-10.0f,10.0f),
			.z = Random_f64_MinMax(5.0f,15.0f)
		}});
	}
}
void Delete(AlxWindow* w){
    Vector_Free(&stars);
}

int main(){
    if(Create("Star Field",1920,1080,1,1,Setup,Update,Delete))
        Start();
    return 0;
}