#include "./void/data.h"
#include "./void/pack.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
// int main()
{


    try{

         
    GameManager gm{hInstance, hPrevInstance,  lpCmdLine,  nShowCmd};

    gm.game();

    
    }catch(exception& e){
        ErrorNotiffication(e.what(),"Main -> main function");
    }

    return EXIT_SUCCESS;
}