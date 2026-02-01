#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"


void Setup(AlxWindow* w){
    
}
void Update(AlxWindow* w){
    if(Stroke(ALX_MOUSE_L).PRESSED){
        
    }

    Clear(BLACK);

}
void Delete(AlxWindow* w){
    
}

int main(){
    if(Create("Star Field",1920,1080,1,1,Setup,Update,Delete))
        Start();
    return 0;
}