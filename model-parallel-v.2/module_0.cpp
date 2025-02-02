#include<iostream>
#include <list>
#include <memory>
#include <string>
#include "parameters.h"
#include "fieldsgrids.h"
#include "particles.h"
#include "vector3.h"
#include "module_0.h"
#include <cmath>
#include "H5Cpp.h"
#include <bitset>
#include <vector>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::make_shared;


//************************************************************************
//************************************************************************
// Generate a grids of pointers which point to the 
// objects of GridsPoints in heap.
//
//************************************************************************
//************************************************************************

GridsPoints***** GridsCreation( )
{ 
//    GridsPoints **a = new GridsPoints* [totalFace * (fieldsGridsSize+1) * (fieldsGridsSize+1) * (fieldsGridsSize+1)];
//    GridsPoints *ptrArray[totalFace][fieldsGridsSize+1][fieldsGridsSize+1][radialGridsSize+1];
    GridsPoints *****ptrArray;
    ptrArray = new GridsPoints****[totalFace];
    for( int face = 0; face < totalFace; face++)
    {
        ptrArray[face] = new GridsPoints***[fieldsGridsSize+3];
        for( int i = 0; i <= fieldsGridsSize+2; i++)
        {
            ptrArray[face][i] = new GridsPoints**[fieldsGridsSize+3];
            for( int j = 0; j <= fieldsGridsSize+2; j++)
            {
                ptrArray[face][i][j] = new GridsPoints*[fieldsGridsSize+1];
            }
        }
    }
    // face 0 (to us)
    for (int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for(int j = 1; j <= fieldsGridsSize+1; j++)
        {
            for(int k = 0; k <= fieldsGridsSize; k++)
            {
                ptrArray[0][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[0][i][j][k]->InttoPos3( 0, i, j, k);                                        
                ptrArray[0][i][j][k]->XYZtoB(ptrArray[0][i][j][k]->Pos3());
                ptrArray[0][i][j][k]->XYZtoVel( update_type);
                ptrArray[0][i][j][k]->XYZtoE();
                ptrArray[0][i][j][k]->XYZtoDensity();
                ptrArray[0][i][j][k]->SetStopSign(0);
                ptrArray[0][i][j][k]->SetTemperature(0.0);
    /*            if( k == fieldsGridsSize) std::cout << ptrArray[0][i][j][k]->Vel3().x() << " "
                    << ptrArray[0][i][j][k]->Vel3().y() << " "
                    << ptrArray[0][i][j][k]->Vel3().z() << std::endl;
    */      }
        }
    }
    
    // face 1 (on the right)
    // share len with face 0
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k =0; k <= fieldsGridsSize; k++)
        {
            ptrArray[1][1][j][k] = ptrArray[0][fieldsGridsSize+1][j][k];
        }
    }

    for( int i = 2; i <= fieldsGridsSize+1; i++)
    {
        for( int j = 1; j <= fieldsGridsSize+1; j++)
        {
            for( int k = 0; k <= fieldsGridsSize; k++)
            {
                ptrArray[1][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[1][i][j][k]->InttoPos3( 1, i, j, k);                                        
                ptrArray[1][i][j][k]->XYZtoB(ptrArray[1][i][j][k]->Pos3());
                ptrArray[1][i][j][k]->XYZtoVel( update_type);
                ptrArray[1][i][j][k]->XYZtoE();     
                ptrArray[1][i][j][k]->XYZtoDensity();
                ptrArray[1][i][j][k]->SetStopSign(0);
                ptrArray[1][i][j][k]->SetTemperature(0.0);                                
            }
        }
    }
    // face 2 (on the top)
    // share len with face 0
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[2][i][1][k] = ptrArray[0][i][fieldsGridsSize+1][k];
        }
    }
    // share len with face 1
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[2][fieldsGridsSize+1][j][k] = ptrArray[1][j][fieldsGridsSize+1][k];
        }
    }
    for( int i = 1; i <= fieldsGridsSize; i++)
    {   
        for( int j = 2; j <= fieldsGridsSize+1; j++)
        {
            for( int k = 0; k <= fieldsGridsSize; k++)
            {
                ptrArray[2][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[2][i][j][k]->InttoPos3( 2, i, j, k);                                        
                ptrArray[2][i][j][k]->XYZtoB(ptrArray[2][i][j][k]->Pos3());
                ptrArray[2][i][j][k]->XYZtoVel( update_type);
                ptrArray[2][i][j][k]->XYZtoE();
                ptrArray[2][i][j][k]->XYZtoDensity();
                ptrArray[2][i][j][k]->SetStopSign(0);
                ptrArray[2][i][j][k]->SetTemperature(0.0);
            }
        }
    }

    // face 4 (on the left)
    // share len with face 0
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[4][fieldsGridsSize+1][j][k] = ptrArray[0][1][j][k];
        }
    }
    // share len with face 2
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[4][i][fieldsGridsSize+1][k] = ptrArray[2][1][fieldsGridsSize+2-i][k];
        }
    }

    for( int i = 1; i <= fieldsGridsSize; i++)
    {
        for( int j = 1; j <= fieldsGridsSize; j++)
        {
            for( int k = 0; k <= fieldsGridsSize; k++)
            {
                ptrArray[4][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[4][i][j][k]->InttoPos3( 4, i, j, k);                                        
                ptrArray[4][i][j][k]->XYZtoB(ptrArray[4][i][j][k]->Pos3());
                ptrArray[4][i][j][k]->XYZtoVel( update_type);
                ptrArray[4][i][j][k]->XYZtoE();
                ptrArray[4][i][j][k]->XYZtoDensity();
                ptrArray[4][i][j][k]->SetStopSign(0);
                ptrArray[4][i][j][k]->SetTemperature(0.0);
            }
        }
    }
    // face 5 (on the bottom)
    // share len with face 0
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[5][i][fieldsGridsSize+1][k] = ptrArray[0][i][1][k];
        }
    }
    // share len with face 1
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[5][fieldsGridsSize+1][j][k] = ptrArray[1][fieldsGridsSize+2-j][1][k];
        }
    }
    // share len with face 4
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[5][1][j][k] = ptrArray[4][j][1][k];
        }
    }
    for( int i = 2; i <= fieldsGridsSize; i++)
    {
        for( int j = 1; j <= fieldsGridsSize; j++)
        {
            for( int k = 0; k <= fieldsGridsSize; k++)
            {
                ptrArray[5][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[5][i][j][k]->InttoPos3( 5, i, j, k);                                        
                ptrArray[5][i][j][k]->XYZtoB(ptrArray[5][i][j][k]->Pos3());
                ptrArray[5][i][j][k]->XYZtoVel( update_type);
                ptrArray[5][i][j][k]->XYZtoE();
                ptrArray[5][i][j][k]->XYZtoDensity();
                ptrArray[5][i][j][k]->SetStopSign(0);
                ptrArray[5][i][j][k]->SetTemperature(0.0);
            }
        }
    }
    // face 3
    // share len with face 1
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[3][1][j][k] = ptrArray[1][fieldsGridsSize+1][j][k];
        }
    }
    // share len with face 2
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[3][i][fieldsGridsSize+1][k] = ptrArray[2][fieldsGridsSize+2-i][fieldsGridsSize+1][k];
        }
    }
    // share len with face 4
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[3][fieldsGridsSize+1][j][k] = ptrArray[4][1][j][k];
        }
    }

    // share len with face 5
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[3][i][1][k] = ptrArray[5][fieldsGridsSize+2-i][1][k];
        }
    }
    for( int i = 2; i <= fieldsGridsSize; i++)
    {
        for( int j = 2; j <= fieldsGridsSize; j++)
        {
            for( int k = 0; k <= fieldsGridsSize; k++)
            {
                ptrArray[3][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[3][i][j][k]->InttoPos3( 3, i, j, k);                                        
                ptrArray[3][i][j][k]->XYZtoB(ptrArray[3][i][j][k]->Pos3());
                ptrArray[3][i][j][k]->XYZtoVel( update_type);
                ptrArray[3][i][j][k]->XYZtoE();
                ptrArray[3][i][j][k]->XYZtoDensity();
                ptrArray[3][i][j][k]->SetStopSign(0);
                ptrArray[3][i][j][k]->SetTemperature(0.0);
            }
        }
    }

    // info lens for adjant face
    //face 0 
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
        ptrArray[0][i][0][k] = ptrArray[5][i][fieldsGridsSize][k]; // bot
        ptrArray[0][fieldsGridsSize+2][i][k] = ptrArray[1][2][i][k]; // right
        ptrArray[0][i][fieldsGridsSize+2][k] = ptrArray[2][i][2][k]; // top
        ptrArray[0][0][i][k] = ptrArray[4][fieldsGridsSize][i][k];  // left
        }
    }
    //face 1
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
        ptrArray[1][i][0][k] = ptrArray[5][fieldsGridsSize][fieldsGridsSize+2-i][k]; // bot
        ptrArray[1][fieldsGridsSize+2][i][k] = ptrArray[3][2][i][k]; // right
        ptrArray[1][i][fieldsGridsSize+2][k] = ptrArray[2][fieldsGridsSize][i][k]; // top
        ptrArray[1][0][i][k] = ptrArray[0][fieldsGridsSize][i][k];  // left
        }
    }
    //face 2
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
        ptrArray[2][i][0][k] = ptrArray[0][i][fieldsGridsSize][k]; // bot
        ptrArray[2][fieldsGridsSize+2][i][k] = ptrArray[1][i][fieldsGridsSize][k]; // right
        ptrArray[2][i][fieldsGridsSize+2][k] = ptrArray[3][fieldsGridsSize+2-i][fieldsGridsSize][k]; // top
        ptrArray[2][0][i][k] = ptrArray[4][fieldsGridsSize+2-i][fieldsGridsSize][k];  // left
        }
    }
    //face 3
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
        ptrArray[3][i][0][k] = ptrArray[5][fieldsGridsSize+2-i][2][k]; // bot
        ptrArray[3][fieldsGridsSize+2][i][k] = ptrArray[4][2][i][k]; // right
        ptrArray[3][i][fieldsGridsSize+2][k] = ptrArray[2][fieldsGridsSize+2-i][fieldsGridsSize][k]; // top
        ptrArray[3][0][i][k] = ptrArray[1][fieldsGridsSize][i][k];  // left
        }
    }
    //face 4
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
        ptrArray[4][i][0][k] = ptrArray[5][2][i][k]; // bot
        ptrArray[4][fieldsGridsSize+2][i][k] = ptrArray[0][2][i][k]; // right
        ptrArray[4][i][fieldsGridsSize+2][k] = ptrArray[2][2][fieldsGridsSize+2-i][k]; // top
        ptrArray[4][0][i][k] = ptrArray[3][fieldsGridsSize][i][k];  // left
        }
    }   
    //face 5
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
        ptrArray[5][i][0][k] = ptrArray[3][fieldsGridsSize+2-i][2][k]; // bot
        ptrArray[5][fieldsGridsSize+2][i][k] = ptrArray[1][fieldsGridsSize+2-i][2][k]; // right
        ptrArray[5][i][fieldsGridsSize+2][k] = ptrArray[0][i][2][k]; // top
        ptrArray[5][0][i][k] = ptrArray[4][i][2][k];  // left
        }
    }    
    
    // Info for not used pointers at four corners of each face
    for( int face = 0; face < totalFace; face++)
    {
        for( int k = 0; k <= fieldsGridsSize; k++)
        {
            ptrArray[face][0][0][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
            ptrArray[face][0][fieldsGridsSize+2][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
            ptrArray[face][fieldsGridsSize+2][0][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
            ptrArray[face][fieldsGridsSize+2][fieldsGridsSize+2][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
        }
    }

    //////////// test of location for peak points 

    cout << "fieldsGridsSize " << fieldsGridsSize  << endl;
//    cout << "sizeof " << sizeof(ptrArray[0])/sizeof(ptrArray[0][0][0][0]) << endl;
    
/*    // face 0, bottom left
    cout <<"0 "<< ptrArray[0][1][1][0]<<" 5 "<< ptrArray[5][1][fieldsGridsSize+1][0] <<" 4 "<< ptrArray[4][fieldsGridsSize+1][1][0] << endl;
    // face 0, bottom right
    cout <<"0 "<< ptrArray[0][fieldsGridsSize+1][1][0]<<" 5 "<< ptrArray[5][fieldsGridsSize+1][fieldsGridsSize+1][0] <<" 1 "<< ptrArray[1][1][1][0] << endl;
    // face 0, top left
    cout <<"0 "<< ptrArray[0][1][fieldsGridsSize+1][0]<<" 2 "<< ptrArray[2][1][1][0] <<" 4 "<< ptrArray[4][fieldsGridsSize+1][fieldsGridsSize+1][0] << endl;
    // face 0, top right
    cout <<"0 "<< ptrArray[0][fieldsGridsSize+1][fieldsGridsSize+1][0]<<" 1 "<< ptrArray[1][1][fieldsGridsSize+1][0] <<" 2 "<< ptrArray[2][fieldsGridsSize+1][1][0] << endl;
    // face 3, bottom left
    cout <<"3 "<< ptrArray[3][1][1][0]<<" 1 "<< ptrArray[1][fieldsGridsSize+1][1][0] <<" 5 "<< ptrArray[5][fieldsGridsSize+1][1][0] << endl;
    // face 3, bottom right
    cout <<"3 "<< ptrArray[3][fieldsGridsSize+1][1][0]<<" 4 "<< ptrArray[4][1][1][0] <<" 5 "<< ptrArray[5][1][1][0] << endl;
    // face 3, top left
    cout <<"3 "<< ptrArray[3][1][fieldsGridsSize+1][0]<<" 1 "<< ptrArray[1][fieldsGridsSize+1][fieldsGridsSize+1][0] <<" 2 "<< ptrArray[2][fieldsGridsSize+1][fieldsGridsSize+1][0] << endl;
    // face 3, top right
    cout <<"3 "<< ptrArray[3][fieldsGridsSize+1][fieldsGridsSize+1][0]<<" 4 "<< ptrArray[4][1][fieldsGridsSize+1][0] <<" 2 "<< ptrArray[2][1][fieldsGridsSize+1][0] << endl;
    //face 0 
    for( int i =0; i < 6; i++)
    {   
        cout << "face " << i << endl;
        cout << "botleft " << ptrArray[i][0][1][0] << " " << ptrArray[i][1][0][0] << endl;
        cout << "botright" << ptrArray[i][fieldsGridsSize+2][1][0] << " " << ptrArray[i][fieldsGridsSize+1][0][0] << endl;
        cout << "topleft " << ptrArray[i][0][fieldsGridsSize+1][0] << " " << ptrArray[i][1][fieldsGridsSize+2][0] << endl;
        cout << "topright" << ptrArray[i][fieldsGridsSize+2][fieldsGridsSize+1][0] << " " << ptrArray[i][fieldsGridsSize+1][fieldsGridsSize+2][0] << endl << endl;        
    }
*/   
    return ptrArray;
}



GridsPoints***** GridsCreation( GridsPoints***** ptrArray, int gridsSize)
{ 
//    GridsPoints **a = new GridsPoints* [totalFace * (fieldsGridsSize+1) * (fieldsGridsSize+1) * (fieldsGridsSize+1)];
//    GridsPoints *ptrArray[totalFace][fieldsGridsSize+1][fieldsGridsSize+1][radialGridsSize+1];

    ptrArray = new GridsPoints****[totalFace];
    for( int face = 0; face < totalFace; face++)
    {
        ptrArray[face] = new GridsPoints***[fieldsGridsSize+3];
        for( int i = 0; i <= fieldsGridsSize+2; i++)
        {
            ptrArray[face][i] = new GridsPoints**[fieldsGridsSize+3];
            for( int j = 0; j <= fieldsGridsSize+2; j++)
            {
                ptrArray[face][i][j] = new GridsPoints*[gridsSize+1];
            }
        }
    }
    // face 0 (to us)
    for (int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for(int j = 1; j <= fieldsGridsSize+1; j++)
        {
            for(int k = 0; k <= gridsSize; k++)
            {
                ptrArray[0][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[0][i][j][k]->InttoPos3( 0, i, j, k);                                        
                ptrArray[0][i][j][k]->XYZtoB(ptrArray[0][i][j][k]->Pos3());
                ptrArray[0][i][j][k]->XYZtoVel( update_type);
                ptrArray[0][i][j][k]->XYZtoE();
                ptrArray[0][i][j][k]->XYZtoDensity();
                ptrArray[0][i][j][k]->SetStopSign(0);
                ptrArray[0][i][j][k]->SetTemperature(0.0);
    /*            if( k == fieldsGridsSize) std::cout << ptrArray[0][i][j][k]->Vel3().x() << " "
                    << ptrArray[0][i][j][k]->Vel3().y() << " "
                    << ptrArray[0][i][j][k]->Vel3().z() << std::endl;
    */      }
        }
    }
    
    // face 1 (on the right)
    // share len with face 0
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k =0; k <= gridsSize; k++)
        {
            ptrArray[1][1][j][k] = ptrArray[0][fieldsGridsSize+1][j][k];
        }
    }

    for( int i = 2; i <= fieldsGridsSize+1; i++)
    {
        for( int j = 1; j <= fieldsGridsSize+1; j++)
        {
            for( int k = 0; k <= gridsSize; k++)
            {
                ptrArray[1][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[1][i][j][k]->InttoPos3( 1, i, j, k);                                        
                ptrArray[1][i][j][k]->XYZtoB(ptrArray[1][i][j][k]->Pos3());
                ptrArray[1][i][j][k]->XYZtoVel( update_type);
                ptrArray[1][i][j][k]->XYZtoE();     
                ptrArray[1][i][j][k]->XYZtoDensity();
                ptrArray[1][i][j][k]->SetStopSign(0);
                ptrArray[1][i][j][k]->SetTemperature(0.0);                                
            }
        }
    }
    // face 2 (on the top)
    // share len with face 0
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[2][i][1][k] = ptrArray[0][i][fieldsGridsSize+1][k];
        }
    }
    // share len with face 1
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[2][fieldsGridsSize+1][j][k] = ptrArray[1][j][fieldsGridsSize+1][k];
        }
    }
    for( int i = 1; i <= fieldsGridsSize; i++)
    {   
        for( int j = 2; j <= fieldsGridsSize+1; j++)
        {
            for( int k = 0; k <= gridsSize; k++)
            {
                ptrArray[2][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[2][i][j][k]->InttoPos3( 2, i, j, k);                                        
                ptrArray[2][i][j][k]->XYZtoB(ptrArray[2][i][j][k]->Pos3());
                ptrArray[2][i][j][k]->XYZtoVel( update_type);
                ptrArray[2][i][j][k]->XYZtoE();
                ptrArray[2][i][j][k]->XYZtoDensity();
                ptrArray[2][i][j][k]->SetStopSign(0);
                ptrArray[2][i][j][k]->SetTemperature(0.0);
            }
        }
    }

    // face 4 (on the left)
    // share len with face 0
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[4][fieldsGridsSize+1][j][k] = ptrArray[0][1][j][k];
        }
    }
    // share len with face 2
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[4][i][fieldsGridsSize+1][k] = ptrArray[2][1][fieldsGridsSize+2-i][k];
        }
    }

    for( int i = 1; i <= fieldsGridsSize; i++)
    {
        for( int j = 1; j <= fieldsGridsSize; j++)
        {
            for( int k = 0; k <= gridsSize; k++)
            {
                ptrArray[4][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[4][i][j][k]->InttoPos3( 4, i, j, k);                                        
                ptrArray[4][i][j][k]->XYZtoB(ptrArray[4][i][j][k]->Pos3());
                ptrArray[4][i][j][k]->XYZtoVel( update_type);
                ptrArray[4][i][j][k]->XYZtoE();
                ptrArray[4][i][j][k]->XYZtoDensity();
                ptrArray[4][i][j][k]->SetStopSign(0);
                ptrArray[4][i][j][k]->SetTemperature(0.0);
            }
        }
    }
    // face 5 (on the bottom)
    // share len with face 0
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[5][i][fieldsGridsSize+1][k] = ptrArray[0][i][1][k];
        }
    }
    // share len with face 1
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[5][fieldsGridsSize+1][j][k] = ptrArray[1][fieldsGridsSize+2-j][1][k];
        }
    }
    // share len with face 4
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[5][1][j][k] = ptrArray[4][j][1][k];
        }
    }
    for( int i = 2; i <= fieldsGridsSize; i++)
    {
        for( int j = 1; j <= fieldsGridsSize; j++)
        {
            for( int k = 0; k <= gridsSize; k++)
            {
                ptrArray[5][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[5][i][j][k]->InttoPos3( 5, i, j, k);                                        
                ptrArray[5][i][j][k]->XYZtoB(ptrArray[5][i][j][k]->Pos3());
                ptrArray[5][i][j][k]->XYZtoVel( update_type);
                ptrArray[5][i][j][k]->XYZtoE();
                ptrArray[5][i][j][k]->XYZtoDensity();
                ptrArray[5][i][j][k]->SetStopSign(0);
                ptrArray[5][i][j][k]->SetTemperature(0.0);
            }
        }
    }
    // face 3
    // share len with face 1
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[3][1][j][k] = ptrArray[1][fieldsGridsSize+1][j][k];
        }
    }
    // share len with face 2
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[3][i][fieldsGridsSize+1][k] = ptrArray[2][fieldsGridsSize+2-i][fieldsGridsSize+1][k];
        }
    }
    // share len with face 4
    for( int j = 1; j <= fieldsGridsSize+1; j++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[3][fieldsGridsSize+1][j][k] = ptrArray[4][1][j][k];
        }
    }

    // share len with face 5
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[3][i][1][k] = ptrArray[5][fieldsGridsSize+2-i][1][k];
        }
    }
    for( int i = 2; i <= fieldsGridsSize; i++)
    {
        for( int j = 2; j <= fieldsGridsSize; j++)
        {
            for( int k = 0; k <= gridsSize; k++)
            {
                ptrArray[3][i][j][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
                ptrArray[3][i][j][k]->InttoPos3( 3, i, j, k);                                        
                ptrArray[3][i][j][k]->XYZtoB(ptrArray[3][i][j][k]->Pos3());
                ptrArray[3][i][j][k]->XYZtoVel( update_type);
                ptrArray[3][i][j][k]->XYZtoE();
                ptrArray[3][i][j][k]->XYZtoDensity();
                ptrArray[3][i][j][k]->SetStopSign(0);
                ptrArray[3][i][j][k]->SetTemperature(0.0);
            }
        }
    }

    // info lens for adjant face
    //face 0 
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
        ptrArray[0][i][0][k] = ptrArray[5][i][fieldsGridsSize][k]; // bot
        ptrArray[0][fieldsGridsSize+2][i][k] = ptrArray[1][2][i][k]; // right
        ptrArray[0][i][fieldsGridsSize+2][k] = ptrArray[2][i][2][k]; // top
        ptrArray[0][0][i][k] = ptrArray[4][fieldsGridsSize][i][k];  // left
        }
    }
    //face 1
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
        ptrArray[1][i][0][k] = ptrArray[5][fieldsGridsSize][fieldsGridsSize+2-i][k]; // bot
        ptrArray[1][fieldsGridsSize+2][i][k] = ptrArray[3][2][i][k]; // right
        ptrArray[1][i][fieldsGridsSize+2][k] = ptrArray[2][fieldsGridsSize][i][k]; // top
        ptrArray[1][0][i][k] = ptrArray[0][fieldsGridsSize][i][k];  // left
        }
    }
    //face 2
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
        ptrArray[2][i][0][k] = ptrArray[0][i][fieldsGridsSize][k]; // bot
        ptrArray[2][fieldsGridsSize+2][i][k] = ptrArray[1][i][fieldsGridsSize][k]; // right
        ptrArray[2][i][fieldsGridsSize+2][k] = ptrArray[3][fieldsGridsSize+2-i][fieldsGridsSize][k]; // top
        ptrArray[2][0][i][k] = ptrArray[4][fieldsGridsSize+2-i][fieldsGridsSize][k];  // left
        }
    }
    //face 3
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
        ptrArray[3][i][0][k] = ptrArray[5][fieldsGridsSize+2-i][2][k]; // bot
        ptrArray[3][fieldsGridsSize+2][i][k] = ptrArray[4][2][i][k]; // right
        ptrArray[3][i][fieldsGridsSize+2][k] = ptrArray[2][fieldsGridsSize+2-i][fieldsGridsSize][k]; // top
        ptrArray[3][0][i][k] = ptrArray[1][fieldsGridsSize][i][k];  // left
        }
    }
    //face 4
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
        ptrArray[4][i][0][k] = ptrArray[5][2][i][k]; // bot
        ptrArray[4][fieldsGridsSize+2][i][k] = ptrArray[0][2][i][k]; // right
        ptrArray[4][i][fieldsGridsSize+2][k] = ptrArray[2][2][fieldsGridsSize+2-i][k]; // top
        ptrArray[4][0][i][k] = ptrArray[3][fieldsGridsSize][i][k];  // left
        }
    }   
    //face 5
    for( int i = 1; i <= fieldsGridsSize+1; i++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
        ptrArray[5][i][0][k] = ptrArray[3][fieldsGridsSize+2-i][2][k]; // bot
        ptrArray[5][fieldsGridsSize+2][i][k] = ptrArray[1][fieldsGridsSize+2-i][2][k]; // right
        ptrArray[5][i][fieldsGridsSize+2][k] = ptrArray[0][i][2][k]; // top
        ptrArray[5][0][i][k] = ptrArray[4][i][2][k];  // left
        }
    }    
    
    // Info for not used pointers at four corners of each face
    for( int face = 0; face < totalFace; face++)
    {
        for( int k = 0; k <= gridsSize; k++)
        {
            ptrArray[face][0][0][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
            ptrArray[face][0][fieldsGridsSize+2][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
            ptrArray[face][fieldsGridsSize+2][0][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
            ptrArray[face][fieldsGridsSize+2][fieldsGridsSize+2][k] = new GridsPoints( 0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0.0, 0.0,
                                                        0.0, 0);
        }
    }

    //////////// test of location for peak points 

    cout << "fieldsGridsSize " << fieldsGridsSize  << endl;
//    cout << "sizeof " << sizeof(ptrArray[0])/sizeof(ptrArray[0][0][0][0]) << endl;
    
/*    // face 0, bottom left
    cout <<"0 "<< ptrArray[0][1][1][0]<<" 5 "<< ptrArray[5][1][fieldsGridsSize+1][0] <<" 4 "<< ptrArray[4][fieldsGridsSize+1][1][0] << endl;
    // face 0, bottom right
    cout <<"0 "<< ptrArray[0][fieldsGridsSize+1][1][0]<<" 5 "<< ptrArray[5][fieldsGridsSize+1][fieldsGridsSize+1][0] <<" 1 "<< ptrArray[1][1][1][0] << endl;
    // face 0, top left
    cout <<"0 "<< ptrArray[0][1][fieldsGridsSize+1][0]<<" 2 "<< ptrArray[2][1][1][0] <<" 4 "<< ptrArray[4][fieldsGridsSize+1][fieldsGridsSize+1][0] << endl;
    // face 0, top right
    cout <<"0 "<< ptrArray[0][fieldsGridsSize+1][fieldsGridsSize+1][0]<<" 1 "<< ptrArray[1][1][fieldsGridsSize+1][0] <<" 2 "<< ptrArray[2][fieldsGridsSize+1][1][0] << endl;
    // face 3, bottom left
    cout <<"3 "<< ptrArray[3][1][1][0]<<" 1 "<< ptrArray[1][fieldsGridsSize+1][1][0] <<" 5 "<< ptrArray[5][fieldsGridsSize+1][1][0] << endl;
    // face 3, bottom right
    cout <<"3 "<< ptrArray[3][fieldsGridsSize+1][1][0]<<" 4 "<< ptrArray[4][1][1][0] <<" 5 "<< ptrArray[5][1][1][0] << endl;
    // face 3, top left
    cout <<"3 "<< ptrArray[3][1][fieldsGridsSize+1][0]<<" 1 "<< ptrArray[1][fieldsGridsSize+1][fieldsGridsSize+1][0] <<" 2 "<< ptrArray[2][fieldsGridsSize+1][fieldsGridsSize+1][0] << endl;
    // face 3, top right
    cout <<"3 "<< ptrArray[3][fieldsGridsSize+1][fieldsGridsSize+1][0]<<" 4 "<< ptrArray[4][1][fieldsGridsSize+1][0] <<" 2 "<< ptrArray[2][1][fieldsGridsSize+1][0] << endl;
    //face 0 
    for( int i =0; i < 6; i++)
    {   
        cout << "face " << i << endl;
        cout << "botleft " << ptrArray[i][0][1][0] << " " << ptrArray[i][1][0][0] << endl;
        cout << "botright" << ptrArray[i][fieldsGridsSize+2][1][0] << " " << ptrArray[i][fieldsGridsSize+1][0][0] << endl;
        cout << "topleft " << ptrArray[i][0][fieldsGridsSize+1][0] << " " << ptrArray[i][1][fieldsGridsSize+2][0] << endl;
        cout << "topright" << ptrArray[i][fieldsGridsSize+2][fieldsGridsSize+1][0] << " " << ptrArray[i][fieldsGridsSize+1][fieldsGridsSize+2][0] << endl << endl;        
    }
*/   
    return ptrArray;
}


//************************************************************************
// Initialize top and bot temp grids
//************************************************************************

void InitializeTempGrids( GridsPoints***** ptrArray, GridsPoints***** ptrArray_bot, GridsPoints***** ptrArray_top, int gridsSize)
{
    int face, i, j, k;
    int k_top;
    for( face = 0; face < totalFace; face++)
    {
        for( i =0; i < fieldsGridsSize; i++)
        {
            for( j = 0; j< fieldsGridsSize; j++)
            {
                for( k=0; k<gridsSize+1; k++)
                {
                    k_top = fieldsGridsSize - gridsSize + k;
                    ptrArray_bot[face][i][j][k]->SetGridsPoints( *ptrArray[face][i][j][k]);
                    ptrArray_top[face][i][j][k]->SetGridsPoints( *ptrArray[face][i][j][k_top]);
                }
            }
        }
    }
}

//************************************************************************
// temp value
//************************************************************************
// FUNCTION // Set up a matrix to store the curl E or B for Faraday's Law
// and for Ampere's Law, or the gradient of Pe. 
// The size of the matrix should be 1 smaller than 
// the size of gridspoints in main doman which is a cubic, which is [fsize+2].
// Therefore, it is [fsize+2][fsize+2][fsize]
// For each face, 8 corner cell should be excluded. ?
// Notice that the curl E or B is at the center of each cell.
// The data structure is array of Vector3, which is created in heap. Return
// a pointer(may not need to be a smart pointer), and would not need to 
// delete, or would be deleted as a smart pointer.

void VectorCellField( Vector3 ***&cellArray)
{
    static Vector3* mem_VectorCellField = new Vector3[ (fieldsGridsSize+2)*(fieldsGridsSize+2)*fieldsGridsSize];
    cellArray = new Vector3**[fieldsGridsSize+2];
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        cellArray[i] = new Vector3*[fieldsGridsSize+2];
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
//            cellArray[i][j] = new Vector3[fieldsGridsSize];
            cellArray[i][j] = mem_VectorCellField + i*(fieldsGridsSize+2)*(fieldsGridsSize)
                            + j* fieldsGridsSize;
            for( int k = 0; k< fieldsGridsSize; k++)
            {
                cellArray[i][j][k] = Vector3(0.0, 0.0, 0.0);
            }
        }
    }
}

void VectorCellField_Vel( Vector3 ***&cellArray)
{
    static Vector3* mem_VectorCellField_Vel = new Vector3[ (fieldsGridsSize+2)*(fieldsGridsSize+2)*fieldsGridsSize];
    cellArray = new Vector3**[fieldsGridsSize+2];
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        cellArray[i] = new Vector3*[fieldsGridsSize+2];
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
            cellArray[i][j] = mem_VectorCellField_Vel + i*(fieldsGridsSize+2)*(fieldsGridsSize)
                            + j* fieldsGridsSize;
            for( int k = 0; k< fieldsGridsSize; k++)
            {
                cellArray[i][j][k] = Vector3(0.0, 0.0, 0.0);
            }
        }
    }
}

void VectorCellField_Grad( Vector3 ***&cellArray)
{
    static Vector3* mem_VectorCellField_Grad = new Vector3[ (fieldsGridsSize+2)*(fieldsGridsSize+2)*fieldsGridsSize];
    cellArray = new Vector3**[fieldsGridsSize+2];
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        cellArray[i] = new Vector3*[fieldsGridsSize+2];
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
            cellArray[i][j] = mem_VectorCellField_Grad + i*(fieldsGridsSize+2)*(fieldsGridsSize)
                            + j* fieldsGridsSize;
            for( int k = 0; k< fieldsGridsSize; k++)
            {
                cellArray[i][j][k] = Vector3(0.0, 0.0, 0.0);
            }
        }
    }
}

// DELET the NEW items
void DEL_VectorCellField( Vector3 ***&cellArray)
{
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
            delete[] cellArray[i][j];
        }
     //   delete[] cellArray[i];
    }
    //delete[] cellArray;
}


//************************************************************************
//************************************************************************
// FUNCTION 
// Value the matrix field using finite volume method, put in the pointer 
// of the MatrixField, value it, and return the pointer.
// Notice that the cell at corners should be absent in calculation.
Vector3*** ValueCurlField( Vector3*** curlArray_in, double*** ptrVolumeCellArray_in, GridsPoints***** ptrArray_in, int face_in, char field_in)
{
//#pragma omp parallel for collapse(3)
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
            for( int k = 0; k < fieldsGridsSize; k++)
            {
                if((i==0&&j==0)||
                            (i==0&&j==fieldsGridsSize+1)||
                            (i==fieldsGridsSize+1&&j==fieldsGridsSize+1)||
                            (i==fieldsGridsSize+1&&j==0))  
                            continue;


        /*        Vector3 test = AreaVectorL( ptrArray_in, face_in, i, j, k);
                std::cout << test.x() << " " << test.y() << " " << test.z() << " " << test.norm();
                int pause;
                std::cin >> pause;
        */
                // for each cell, calculate sum(n X B( on face)) and devided by
                // Volume to get the curl B at the center of cell
                Vector3 temp = AreaVectorL( ptrArray_in, face_in, i, j, k).CrossProduct(
                               FaceFieldVectorL(ptrArray_in, face_in, i, j, k, field_in));
                        temp = temp.PlusProduct(
                               AreaVectorR( ptrArray_in, face_in, i, j, k).CrossProduct(
                               FaceFieldVectorR(ptrArray_in, face_in, i, j, k, field_in)));
                        temp = temp.PlusProduct(
                               AreaVectorT( ptrArray_in, face_in, i, j, k).CrossProduct(
                               FaceFieldVectorT(ptrArray_in, face_in, i, j, k, field_in)));
                        temp = temp.PlusProduct(
                               AreaVectorBot( ptrArray_in, face_in, i, j, k).CrossProduct(
                               FaceFieldVectorBot(ptrArray_in, face_in, i, j, k, field_in)));
                        temp = temp.PlusProduct(
                               AreaVectorF( ptrArray_in, face_in, i, j, k).CrossProduct(
                               FaceFieldVectorF(ptrArray_in, face_in, i, j, k, field_in)));
                        temp = temp.PlusProduct(
                               AreaVectorBack( ptrArray_in, face_in, i, j, k).CrossProduct(
                               FaceFieldVectorBack(ptrArray_in, face_in, i, j, k, field_in)));
                double volumetemp = ptrVolumeCellArray_in[i][j][k];

                temp = temp.ScaleProduct( 1.0 / volumetemp);
                curlArray_in[i][j][k].SetVector3( temp); 
/*
                std::cout << face_in << field_in << i << j << k << " " << temp.norm() << std::endl;;
                int pause;
                if( temp.norm() !=0 ){
     //           std::cin >> pause;
                    }
 */           }
        }
    }
    return curlArray_in;
}


//************************************************************************
//************************************************************************
// FUNCTION 
// Value gradient field of Pe.
// gradientArray_in is in size of ( fsize+2 * fsize+2 * fsize) with vector3
// ptrVolumeCellArray is in size of ( fsize+2 * fsize+2 * fsize) with double
// Pe = n k T, in which n is the number density, k is the boltzmann constant, and T is the Te
Vector3*** ValueGradient(Vector3*** gradientArray_in, double*** ptrVolumeCellArray_in, GridsPoints***** ptrArray_in, int face_in, char char_in)
{
//#pragma omp parallel for collapse(3)
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
            for( int k = 0; k < fieldsGridsSize; k++)
            {
                if((i==0&&j==0)||
                            (i==0&&j==fieldsGridsSize+1)||
                            (i==fieldsGridsSize+1&&j==fieldsGridsSize+1)||
                            (i==fieldsGridsSize+1&&j==0))
                continue;

                Vector3 temp;

                if( char_in == 'P') // electron pressure Pe
                {
                // for each cell, calculate sum of n(face vector) * densities and devided by
                // Volume to get the gradient at the center of cell  
                temp = AreaVectorL( ptrArray_in, face_in, i, j, k).ScaleProduct(
                           FaceNumberDensityL(ptrArray_in, face_in, i, j, k) * FaceTemperatureL(ptrArray_in, face_in, i, j, k) * boltzmann_k);
                temp = temp.PlusProduct(
                               AreaVectorR( ptrArray_in, face_in, i, j, k).ScaleProduct(
                               FaceNumberDensityR(ptrArray_in, face_in, i, j, k) * FaceTemperatureR(ptrArray_in, face_in, i, j, k) * boltzmann_k));
                temp = temp.PlusProduct(
                               AreaVectorT( ptrArray_in, face_in, i, j, k).ScaleProduct(
                               FaceNumberDensityT(ptrArray_in, face_in, i, j, k) * FaceTemperatureT(ptrArray_in, face_in, i, j, k) * boltzmann_k));
                temp = temp.PlusProduct(
                               AreaVectorBot( ptrArray_in, face_in, i, j, k).ScaleProduct(
                               FaceNumberDensityBot(ptrArray_in, face_in, i, j, k) * FaceTemperatureBot(ptrArray_in, face_in, i, j, k) * boltzmann_k));
                temp = temp.PlusProduct(
                               AreaVectorF( ptrArray_in, face_in, i, j, k).ScaleProduct(
                               FaceNumberDensityF(ptrArray_in, face_in, i, j, k) * FaceTemperatureF(ptrArray_in, face_in, i, j, k) * boltzmann_k));
                temp = temp.PlusProduct(
                               AreaVectorBack( ptrArray_in, face_in, i, j, k).ScaleProduct(
                               FaceNumberDensityBack(ptrArray_in, face_in, i, j, k) * FaceTemperatureBack(ptrArray_in, face_in, i, j, k) * boltzmann_k));
                double volumetemp = ptrVolumeCellArray_in[i][j][k];
                temp = temp.ScaleProduct(1/volumetemp);
   //             std::cout << volumetemp << " " ;
     //           std::cout << " --> " << temp.x() << " " << temp.y() << " " << temp.z() << std::endl;
                gradientArray_in[i][j][k].SetVector3(temp); 
                } 
                else    // gradient |B|
                {
                temp = AreaVectorL( ptrArray_in, face_in, i, j, k).ScaleProduct( FaceNormBL(ptrArray_in, face_in, i, j, k) );
                temp = temp.PlusProduct(
                               AreaVectorR( ptrArray_in, face_in, i, j, k).ScaleProduct( FaceNormBR(ptrArray_in, face_in, i, j, k) ));
                temp = temp.PlusProduct(
                               AreaVectorT( ptrArray_in, face_in, i, j, k).ScaleProduct( FaceNormBT(ptrArray_in, face_in, i, j, k) ));
                temp = temp.PlusProduct(
                               AreaVectorBot( ptrArray_in, face_in, i, j, k).ScaleProduct( FaceNormBBot(ptrArray_in, face_in, i, j, k) ));
                temp = temp.PlusProduct(
                               AreaVectorF( ptrArray_in, face_in, i, j, k).ScaleProduct( FaceNormBF(ptrArray_in, face_in, i, j, k) ));
                temp = temp.PlusProduct(
                               AreaVectorBack( ptrArray_in, face_in, i, j, k).ScaleProduct( FaceNormBBack(ptrArray_in, face_in, i, j, k) ));
                double volumetemp = ptrVolumeCellArray_in[i][j][k];
                temp = temp.ScaleProduct(1/volumetemp);
                gradientArray_in[i][j][k].SetVector3(temp); 
                }
                
            }
        }
    }
    return gradientArray_in;
}


//************************************************************************
//************************************************************************
// FUNCTION 
// UpdateVe3
void UpdateVe3( Vector3*** curlField_in, GridsPoints***** ptrArray_in, int face_in)
{   
//#pragma omp parallel for collapse(3)
    for( int i = 1; i < fieldsGridsSize+2; i++)
    {
        for( int j = 1; j < fieldsGridsSize+2; j++)
        {
            for( int k = 1; k < fieldsGridsSize; k++)
            {
                Vector3 curl_field = Vector3(0.0, 0.0, 0.0);
                    
                if(i==1&&j==1) 
                {
                // gradPe at gridspoints
                curl_field = curlField_in[1][0][k-1].PlusProduct(
                                    curlField_in[1][1][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[0][1][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][0][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[0][1][k]).ScaleProduct(1.0/6.0);            
                }
                else if(i==1&&j==fieldsGridsSize+1) 
                {
                
                curl_field = curlField_in[1][fieldsGridsSize+1][k-1].PlusProduct(
                                    curlField_in[1][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[0][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][fieldsGridsSize+1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][fieldsGridsSize][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[0][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==fieldsGridsSize+1)
                {
                curl_field = curlField_in[fieldsGridsSize][fieldsGridsSize+1][k-1].PlusProduct(
                                    curlField_in[fieldsGridsSize][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[fieldsGridsSize+1][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][fieldsGridsSize+1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][fieldsGridsSize][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize+1][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==1) 
                {
                curl_field = curlField_in[fieldsGridsSize][0][k-1].PlusProduct(
                                    curlField_in[fieldsGridsSize][1][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[fieldsGridsSize+1][1][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][0][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize+1][1][k]).ScaleProduct(1.0/6.0);                
                } else
                {
                curl_field = curlField_in[i-1][j-1][k-1].PlusProduct(
                                    curlField_in[i][j-1][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[i-1][j][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i][j][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i-1][j-1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i][j-1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i-1][j][k]);    
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i][j][k]).ScaleProduct(1.0/8.0);
                }
                ptrArray_in[face_in][i][j][k]->updateve3(curl_field);
            }
        }
    }
}


//************************************************************************
//************************************************************************
// FUNCTION NOT used but is a good oppinion
// As in the updating curlField and gradientPe array, some variables are
// repeating calculating, it is suitable to put them in one function.
// Therefore, we need three matrix of curlB, curlE, and gradientPe. 
// Assume they are curlB, curlE and gradPe, respectively.
void updateCellMatrix(Vector3**** curlB_in, Vector3**** curlE_in,
                      Vector3**** gradPe_in, GridsPoints***** ptrArray_in, int face_in)
{
     for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {
            for( int k = 0; k < fieldsGridsSize+2; k++)
            {
                if((i==0&&j==0)||
                            (i==0&&j==fieldsGridsSize+1)||
                            (i==fieldsGridsSize+1&&j==fieldsGridsSize+1)||
                            (i==fieldsGridsSize+1&&j==0) )
                continue;
                // Volume
                double volumetemp = CellVolume(ptrArray_in, face_in, i, j, k);
                // AreaVectors
                Vector3 nL = AreaVectorL( ptrArray_in, face_in, i, j, k);
                Vector3 nR = AreaVectorR( ptrArray_in, face_in, i, j, k);
                Vector3 nT = AreaVectorT( ptrArray_in, face_in, i, j, k);
                Vector3 nBot= AreaVectorBot( ptrArray_in, face_in, i, j, k);
                Vector3 nF = AreaVectorF( ptrArray_in, face_in, i, j, k);
                Vector3 nBack = AreaVectorBack( ptrArray_in, face_in, i, j, k);

                // for each cell, calculate sum of n(vector) * densities and devided by
                // Volume to get the gradient at the center of cell
                
                Vector3 tempGrad = nL.ScaleProduct(
                               FaceDensityL(ptrArray_in, face_in, i, j, k));
                        tempGrad = tempGrad.PlusProduct(
                               nR.ScaleProduct(
                               FaceDensityR(ptrArray_in, face_in, i, j, k)));
                        tempGrad = tempGrad.PlusProduct(
                               nT.ScaleProduct(
                               FaceDensityT(ptrArray_in, face_in, i, j, k)));
                        tempGrad = tempGrad.PlusProduct(
                               nBot.ScaleProduct(
                               FaceDensityBot(ptrArray_in, face_in, i, j, k)));
                        tempGrad = tempGrad.PlusProduct(
                               nF.ScaleProduct(
                               FaceDensityF(ptrArray_in, face_in, i, j, k)));
                        tempGrad = tempGrad.PlusProduct(
                               nBack.ScaleProduct(
                               FaceDensityBack(ptrArray_in, face_in, i, j, k)));

                
                tempGrad = tempGrad.ScaleProduct(1/volumetemp);
                gradPe_in[i][j][k]->SetVector3(tempGrad); 

                Vector3 tempCurlB = nL.CrossProduct(
                               FaceFieldVectorL(ptrArray_in, face_in, i, j, k, 'B'));
                        tempCurlB = tempCurlB.PlusProduct(
                               nR.CrossProduct(
                               FaceFieldVectorR(ptrArray_in, face_in, i, j, k, 'B')));
                        tempCurlB = tempCurlB.PlusProduct(
                               nT.CrossProduct(
                               FaceFieldVectorT(ptrArray_in, face_in, i, j, k, 'B')));
                        tempCurlB = tempCurlB.PlusProduct(
                               nBot.CrossProduct(
                               FaceFieldVectorBot(ptrArray_in, face_in, i, j, k, 'B')));
                        tempCurlB = tempCurlB.PlusProduct(
                               nF.CrossProduct(
                               FaceFieldVectorF(ptrArray_in, face_in, i, j, k, 'B')));
                        tempCurlB = tempCurlB.PlusProduct(
                               nBack.CrossProduct(
                               FaceFieldVectorBack(ptrArray_in, face_in, i, j, k, 'B')));

                tempCurlB = tempCurlB.ScaleProduct(1/volumetemp);
                curlB_in[i][j][k]->SetVector3(tempCurlB); 

                Vector3 tempCurlE = nL.CrossProduct(
                               FaceFieldVectorL(ptrArray_in, face_in, i, j, k, 'E'));
                        tempCurlE = tempCurlE.PlusProduct(
                               nR.CrossProduct(
                               FaceFieldVectorR(ptrArray_in, face_in, i, j, k, 'E')));
                        tempCurlE = tempCurlE.PlusProduct(
                               nT.CrossProduct(
                               FaceFieldVectorT(ptrArray_in, face_in, i, j, k, 'E')));
                        tempCurlE = tempCurlE.PlusProduct(
                               nBot.CrossProduct(
                               FaceFieldVectorBot(ptrArray_in, face_in, i, j, k, 'E')));
                        tempCurlE = tempCurlE.PlusProduct(
                               nF.CrossProduct(
                               FaceFieldVectorF(ptrArray_in, face_in, i, j, k, 'E')));
                        tempCurlE = tempCurlE.PlusProduct(
                               nBack.CrossProduct(
                               FaceFieldVectorBack(ptrArray_in, face_in, i, j, k, 'E')));

                tempCurlE = tempCurlE.ScaleProduct(1/volumetemp);
                curlE_in[i][j][k]->SetVector3(tempCurlE); 
            }
        }
    }
}


//************************************************************************
//************************************************************************
// FUNCTION
// Each calculation are on the girds.
// Update E at grids for ve = vi ( no current)
// Update E at grids for ve ( with current)
// Used in the initialization function
void UpdateE3( Vector3*** gradPe_in, GridsPoints***** ptrArray_in, int face_in)
{

//#pragma omp parallel for collapse(3)

    for( int i = 1; i < fieldsGridsSize+2; i++)
    {
        for( int j = 1; j < fieldsGridsSize+2; j++)
        {
            for( int k = tempGridsCellLevel+1; k < fieldsGridsSize - tempGridsCellLevel; k++)
            {
                Vector3 tempGradPe = Vector3(0.0, 0.0, 0.0);
                    
                if(i==1&&j==1) 
                {
                // gradPe at gridspoints
                tempGradPe = gradPe_in[1][0][k-1].PlusProduct(
                                    gradPe_in[1][1][k-1]);
                tempGradPe = tempGradPe.PlusProduct(           
                                    gradPe_in[0][1][k-1]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[1][0][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[1][1][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[0][1][k]).ScaleProduct(1.0/6.0);            
                }
                else if(i==1&&j==fieldsGridsSize+1) 
                {
                
                tempGradPe = gradPe_in[1][fieldsGridsSize+1][k-1].PlusProduct(
                                    gradPe_in[1][fieldsGridsSize][k-1]);
                tempGradPe = tempGradPe.PlusProduct(           
                                    gradPe_in[0][fieldsGridsSize][k-1]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[1][fieldsGridsSize+1][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[1][fieldsGridsSize][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[0][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==fieldsGridsSize+1)
                {
                tempGradPe = gradPe_in[fieldsGridsSize][fieldsGridsSize+1][k-1].PlusProduct(
                                    gradPe_in[fieldsGridsSize][fieldsGridsSize][k-1]);
                tempGradPe = tempGradPe.PlusProduct(           
                                    gradPe_in[fieldsGridsSize+1][fieldsGridsSize][k-1]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[fieldsGridsSize][fieldsGridsSize+1][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[fieldsGridsSize][fieldsGridsSize][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[fieldsGridsSize+1][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==1) 
                {
                tempGradPe = gradPe_in[fieldsGridsSize][0][k-1].PlusProduct(
                                    gradPe_in[fieldsGridsSize][1][k-1]);
                tempGradPe = tempGradPe.PlusProduct(           
                                    gradPe_in[fieldsGridsSize+1][1][k-1]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[fieldsGridsSize][0][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[fieldsGridsSize][1][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[fieldsGridsSize+1][1][k]).ScaleProduct(1.0/6.0);                
                } else
                {
                tempGradPe = gradPe_in[i-1][j-1][k-1].PlusProduct(
                                    gradPe_in[i][j-1][k-1]);
                tempGradPe = tempGradPe.PlusProduct(           
                                    gradPe_in[i-1][j][k-1]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[i][j][k-1]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[i-1][j-1][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[i][j-1][k]);
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[i-1][j][k]);    
                tempGradPe = tempGradPe.PlusProduct(
                                    gradPe_in[i][j][k]).ScaleProduct(1.0/8.0);
                }
                // update E
                ptrArray_in[face_in][i][j][k]->updateE(tempGradPe);
            }
        }
    }        
}




//************************************************************************
//************************************************************************
// FUNCTION
// UpdateB3 vased on faraday's law

void UpdateB3( Vector3*** curlField_in, GridsPoints***** ptrArray_in, int face_in)
{

#pragma omp parallel for collapse(3)

    for( int i = 1; i < fieldsGridsSize+2; i++)
    {
        for( int j = 1; j < fieldsGridsSize+2; j++)
        {
            for( int k = 1; k < fieldsGridsSize; k++)
            {
                Vector3 curl_field = Vector3(0.0, 0.0, 0.0);
                    
                if(i==1&&j==1) 
                {
                // gradPe at gridspoints
                curl_field = curlField_in[1][0][k-1].PlusProduct(
                                    curlField_in[1][1][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[0][1][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][0][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[0][1][k]).ScaleProduct(1.0/6.0);            
                }
                else if(i==1&&j==fieldsGridsSize+1) 
                {
                
                curl_field = curlField_in[1][fieldsGridsSize+1][k-1].PlusProduct(
                                    curlField_in[1][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[0][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][fieldsGridsSize+1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[1][fieldsGridsSize][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[0][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==fieldsGridsSize+1)
                {
                curl_field = curlField_in[fieldsGridsSize][fieldsGridsSize+1][k-1].PlusProduct(
                                    curlField_in[fieldsGridsSize][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[fieldsGridsSize+1][fieldsGridsSize][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][fieldsGridsSize+1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][fieldsGridsSize][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize+1][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==1) 
                {
                curl_field = curlField_in[fieldsGridsSize][0][k-1].PlusProduct(
                                    curlField_in[fieldsGridsSize][1][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[fieldsGridsSize+1][1][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][0][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize][1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[fieldsGridsSize+1][1][k]).ScaleProduct(1.0/6.0);                
                } else
                {
                curl_field = curlField_in[i-1][j-1][k-1].PlusProduct(
                                    curlField_in[i][j-1][k-1]);
                curl_field = curl_field.PlusProduct(           
                                    curlField_in[i-1][j][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i][j][k-1]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i-1][j-1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i][j-1][k]);
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i-1][j][k]);    
                curl_field = curl_field.PlusProduct(
                                    curlField_in[i][j][k]).ScaleProduct(1.0/8.0);
                }
                // update B
                ptrArray_in[face_in][i][j][k]->updatedB(curl_field);
            }
        }
    }        
}


//************************************************************************
//************************************************************************
// FUNCTION
// Each calculation are on the girds.
// Calculate the grad|B| on the gridspoints
void UpdateGradBNorm( Vector3*** gradBNorm_in, GridsPoints***** ptrArray_in, int face_in)
{

#pragma omp parallel for collapse(3)

    for( int i = 1; i < fieldsGridsSize+2; i++)
    {
        for( int j = 1; j < fieldsGridsSize+2; j++)
        {
            for( int k = 1; k < fieldsGridsSize; k++)
            {
                Vector3 tempGradBNorm = Vector3(0.0, 0.0, 0.0);
                    
                if(i==1&&j==1) 
                {
                // gradPe at gridspoints
                tempGradBNorm = gradBNorm_in[1][0][k-1].PlusProduct(
                                    gradBNorm_in[1][1][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(           
                                    gradBNorm_in[0][1][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[1][0][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[1][1][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[0][1][k]).ScaleProduct(1.0/6.0);            
                }
                else if(i==1&&j==fieldsGridsSize+1) 
                {
                
                tempGradBNorm = gradBNorm_in[1][fieldsGridsSize+1][k-1].PlusProduct(
                                    gradBNorm_in[1][fieldsGridsSize][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(           
                                    gradBNorm_in[0][fieldsGridsSize][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[1][fieldsGridsSize+1][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[1][fieldsGridsSize][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[0][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==fieldsGridsSize+1)
                {
                tempGradBNorm = gradBNorm_in[fieldsGridsSize][fieldsGridsSize+1][k-1].PlusProduct(
                                    gradBNorm_in[fieldsGridsSize][fieldsGridsSize][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(           
                                    gradBNorm_in[fieldsGridsSize+1][fieldsGridsSize][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[fieldsGridsSize][fieldsGridsSize+1][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[fieldsGridsSize][fieldsGridsSize][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[fieldsGridsSize+1][fieldsGridsSize][k]).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==1) 
                {
                tempGradBNorm = gradBNorm_in[fieldsGridsSize][0][k-1].PlusProduct(
                                    gradBNorm_in[fieldsGridsSize][1][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(           
                                    gradBNorm_in[fieldsGridsSize+1][1][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[fieldsGridsSize][0][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[fieldsGridsSize][1][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[fieldsGridsSize+1][1][k]).ScaleProduct(1.0/6.0);                
                } else
                {
                tempGradBNorm = gradBNorm_in[i-1][j-1][k-1].PlusProduct(
                                    gradBNorm_in[i][j-1][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(           
                                    gradBNorm_in[i-1][j][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[i][j][k-1]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[i-1][j-1][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[i][j-1][k]);
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[i-1][j][k]);    
                tempGradBNorm = tempGradBNorm.PlusProduct(
                                    gradBNorm_in[i][j][k]).ScaleProduct(1.0/8.0);
                }
                // update gradB3
                ptrArray_in[face_in][i][j][k]->UpdateGradBNorm(tempGradBNorm);
            }
        }
    }        
}






//************************************************************************
//************************************************************************
// FUNCTION
// Printout the gridpoints on the girds as hdf5 format
// Step 1: Generate a new matrix fulling with gridspoints class
// Step 2: Print out it as .h5
void PrintOutHdf5(  GridsPoints***** ptrArray_in, 
                    int timeline, 
                    int h5FileCheck_in)
{
    using namespace H5;
    char filename[80];
    sprintf( filename, "ArrayOfGrids_%d", timeline);

    H5std_string FILE_NAME( "GridsData.h5");
    H5std_string DATASET_NAME( filename);
    H5std_string DATASET_CONST_NAME( "ArrayOfGrids_const");

    H5std_string MEMBERx( "x");
    H5std_string MEMBERy( "y");
    H5std_string MEMBERz( "z");

    H5std_string MEMBER_pos3( "pos3");
    H5std_string MEMBER_e3( "e3");

    H5std_string MEMBER_b3( "b3");
    H5std_string MEMBER_dB3( "dB3");
    H5std_string MEMBER_gradB3( "gradB3");

    H5std_string MEMBER_ve3( "ve3");
    H5std_string MEMBER_v3( "v3");
    H5std_string MEMBER_vH3( "vH3");
    H5std_string MEMBER_vHe3( "vHe3");
    H5std_string MEMBER_vO3( "vO3");

    H5std_string MEMBER_density_H( "densityH");
    H5std_string MEMBER_density_He( "densityHe");
    H5std_string MEMBER_density_O( "densityO");
    H5std_string MEMBER_density( "density");
    H5std_string MEMBER_te( "temperature");

    const int RANK = 4;

    typedef struct Vector3_h5{
        double v_x;
        double v_y;
        double v_z;
    } Vector3_h5;

    typedef struct GridsPoints_h5{
        Vector3_h5 e3;
        Vector3_h5 dB3;
        Vector3_h5 gradB3;

        Vector3_h5 ve3;
        Vector3_h5 v3;
        Vector3_h5 vH3;
        Vector3_h5 vHe3;
        Vector3_h5 vO3;

        double density;
        double density_H;
        double density_He;
        double density_O;
    } GridsPoints_h5;   // varies with timeline

    typedef struct GridsPoints_const_h5{
        Vector3_h5 pos3;
        Vector3_h5 b3;
        double temperature;
        
        Vector3_h5 e3;
        Vector3_h5 v3;

        double density_H;
        double density_He;
        double density_O;

    } GridsPoints_const_h5;     // dont varies with timeline


    // Apply for continus memory 
    GridsPoints_h5* data_mem = new GridsPoints_h5[totalFace* (1+fieldsGridsSize)* (1+fieldsGridsSize)* (1+fieldsGridsSize)];
    GridsPoints_h5**** array_data = new GridsPoints_h5***[totalFace];
    for( int face=0; face<totalFace; face++)
    {
        array_data[face] = new GridsPoints_h5**[1+fieldsGridsSize];
        for( int i = 0; i< 1+fieldsGridsSize; i++)
        {
            array_data[face][i] = new GridsPoints_h5*[1+fieldsGridsSize];
            for( int j=0; j< 1+fieldsGridsSize; j++)
            {
     //           array_data[face][i][j] = new GridsPoints_h5[1+fieldsGridsSize];
                array_data[face][i][j] = data_mem + face*(1+fieldsGridsSize)*(1+fieldsGridsSize)*(1+fieldsGridsSize)+
                                         i*(1+fieldsGridsSize)*(1+fieldsGridsSize)+
                                         j*(1+fieldsGridsSize);

                for( int k = 0; k < 1 + fieldsGridsSize; k++)
                {
                    array_data[face][i][j][k].e3 
                        = {ptrArray_in[face][i+1][j+1][k]->E3().x(), ptrArray_in[face][i+1][j+1][k]->E3().y(), ptrArray_in[face][i+1][j+1][k]->E3().z()} ;

                    array_data[face][i][j][k].dB3 
                        = {ptrArray_in[face][i+1][j+1][k]->DB3().x(), ptrArray_in[face][i+1][j+1][k]->DB3().y(), ptrArray_in[face][i+1][j+1][k]->DB3().z()} ;
                    array_data[face][i][j][k].gradB3 
                        = {ptrArray_in[face][i+1][j+1][k]->GradB3().x(), ptrArray_in[face][i+1][j+1][k]->GradB3().y(), ptrArray_in[face][i+1][j+1][k]->GradB3().z()} ;
                    
                    array_data[face][i][j][k].ve3 
                        = {ptrArray_in[face][i+1][j+1][k]->Vel_e3().x(), ptrArray_in[face][i+1][j+1][k]->Vel_e3().y(), ptrArray_in[face][i+1][j+1][k]->Vel_e3().z()} ;
                    
                    array_data[face][i][j][k].v3 
                        = {ptrArray_in[face][i+1][j+1][k]->Vel3().x(), ptrArray_in[face][i+1][j+1][k]->Vel3().y(), ptrArray_in[face][i+1][j+1][k]->Vel3().z()} ;
                    array_data[face][i][j][k].vH3 
                        = {ptrArray_in[face][i+1][j+1][k]->VelH3().x(), ptrArray_in[face][i+1][j+1][k]->VelH3().y(), ptrArray_in[face][i+1][j+1][k]->VelH3().z()} ;
                    array_data[face][i][j][k].vHe3 
                        = {ptrArray_in[face][i+1][j+1][k]->VelHe3().x(), ptrArray_in[face][i+1][j+1][k]->VelHe3().y(), ptrArray_in[face][i+1][j+1][k]->VelHe3().z()} ;
                    array_data[face][i][j][k].vO3 
                        = {ptrArray_in[face][i+1][j+1][k]->VelO3().x(), ptrArray_in[face][i+1][j+1][k]->VelO3().y(), ptrArray_in[face][i+1][j+1][k]->VelO3().z()} ;

                    array_data[face][i][j][k].density
                        = ptrArray_in[face][i+1][j+1][k]->Density();
                    array_data[face][i][j][k].density_H
                        = ptrArray_in[face][i+1][j+1][k]->Density_H();
                    array_data[face][i][j][k].density_He
                        = ptrArray_in[face][i+1][j+1][k]->Density_He();
                    array_data[face][i][j][k].density_O
                        = ptrArray_in[face][i+1][j+1][k]->Density_O();
                    //    std::cout << array_data[face][i][j][k].b3.v_x << std::endl;
                }
            }
        }
    }
    
    GridsPoints_const_h5* data_mem_const = new GridsPoints_const_h5[totalFace* (1+fieldsGridsSize)* (1+fieldsGridsSize)* (1+fieldsGridsSize)];
    GridsPoints_const_h5**** array_data_const = new GridsPoints_const_h5***[totalFace];
    for( int face=0; face<totalFace; face++)
    {
        array_data_const[face] = new GridsPoints_const_h5**[1+fieldsGridsSize];
        for( int i = 0; i< 1+fieldsGridsSize; i++)
        {
            array_data_const[face][i] = new GridsPoints_const_h5*[1+fieldsGridsSize];
            for( int j=0; j< 1+fieldsGridsSize; j++)
            {
 //               array_data_const[face][i][j] = new GridsPoints_const_h5[1+fieldsGridsSize];
                array_data_const[face][i][j] = data_mem_const + face*(1+fieldsGridsSize)*(1+fieldsGridsSize)*(1+fieldsGridsSize)+
                                         i*(1+fieldsGridsSize)*(1+fieldsGridsSize)+
                                         j*(1+fieldsGridsSize);

                for( int k = 0; k < 1 + fieldsGridsSize; k++)
                {       
                    array_data_const[face][i][j][k].pos3 
                        = {ptrArray_in[face][i+1][j+1][k]->Pos3().x(), ptrArray_in[face][i+1][j+1][k]->Pos3().y(), ptrArray_in[face][i+1][j+1][k]->Pos3().z()} ;
                    
                    array_data_const[face][i][j][k].b3 
                        = {ptrArray_in[face][i+1][j+1][k]->B3_base().x(), ptrArray_in[face][i+1][j+1][k]->B3_base().y(), ptrArray_in[face][i+1][j+1][k]->B3_base().z()} ;
                    
                    array_data_const[face][i][j][k].temperature = ptrArray_in[face][i+1][j+1][k]->Temperature();
                    
                    array_data_const[face][i][j][k].e3 
                        = {ptrArray_in[face][i+1][j+1][k]->E3().x(), ptrArray_in[face][i+1][j+1][k]->E3().y(), ptrArray_in[face][i+1][j+1][k]->E3().z()} ;
                    
                    array_data_const[face][i][j][k].v3 
                        = {ptrArray_in[face][i+1][j+1][k]->Vel3().x(), ptrArray_in[face][i+1][j+1][k]->Vel3().y(), ptrArray_in[face][i+1][j+1][k]->Vel3().z()} ;
                    
                    array_data_const[face][i][j][k].density_H
                        = ptrArray_in[face][i+1][j+1][k]->Density_H();
                    
                    array_data_const[face][i][j][k].density_He
                        = ptrArray_in[face][i+1][j+1][k]->Density_He();
                    
                    array_data_const[face][i][j][k].density_O
                        = ptrArray_in[face][i+1][j+1][k]->Density_O();
                    

                }
            }
        }
    }            

    Exception::dontPrint();



    hsize_t dim[] = {totalFace,fieldsGridsSize+1,fieldsGridsSize+1,fieldsGridsSize+1};
    DataSpace space( RANK, dim);


        // vector elements
        CompType mtype_vector3( sizeof( Vector3_h5));
        mtype_vector3.insertMember( MEMBERx, HOFFSET(Vector3_h5,v_x), PredType::NATIVE_DOUBLE);
        mtype_vector3.insertMember( MEMBERy, HOFFSET(Vector3_h5,v_y), PredType::NATIVE_DOUBLE);
        mtype_vector3.insertMember( MEMBERz, HOFFSET(Vector3_h5,v_z), PredType::NATIVE_DOUBLE);

        // const group variables
        CompType mtype_grids_const( sizeof( GridsPoints_const_h5));
        mtype_grids_const.insertMember( MEMBER_pos3, HOFFSET(GridsPoints_const_h5,pos3), mtype_vector3);
        mtype_grids_const.insertMember( MEMBER_b3, HOFFSET(GridsPoints_const_h5,b3), mtype_vector3);

        mtype_grids_const.insertMember( MEMBER_te, HOFFSET(GridsPoints_const_h5,temperature), PredType::NATIVE_DOUBLE);

        mtype_grids_const.insertMember( MEMBER_e3, HOFFSET(GridsPoints_const_h5,e3), mtype_vector3);
        mtype_grids_const.insertMember( MEMBER_v3, HOFFSET(GridsPoints_const_h5,v3), mtype_vector3);

        mtype_grids_const.insertMember( MEMBER_density_H, HOFFSET(GridsPoints_const_h5,density_H), PredType::NATIVE_DOUBLE);
        mtype_grids_const.insertMember( MEMBER_density_He, HOFFSET(GridsPoints_const_h5,density_He), PredType::NATIVE_DOUBLE);
        mtype_grids_const.insertMember( MEMBER_density_O, HOFFSET(GridsPoints_const_h5,density_O), PredType::NATIVE_DOUBLE);

        // non-const group variables
        CompType mtype_grids( sizeof( GridsPoints_h5));
        mtype_grids.insertMember( MEMBER_e3, HOFFSET(GridsPoints_h5,e3), mtype_vector3);
        mtype_grids.insertMember( MEMBER_dB3, HOFFSET(GridsPoints_h5,dB3), mtype_vector3);
        mtype_grids.insertMember( MEMBER_gradB3, HOFFSET(GridsPoints_h5,gradB3), mtype_vector3);
        
        mtype_grids.insertMember( MEMBER_ve3, HOFFSET(GridsPoints_h5,ve3), mtype_vector3);
        mtype_grids.insertMember( MEMBER_v3, HOFFSET(GridsPoints_h5,v3), mtype_vector3);
        mtype_grids.insertMember( MEMBER_vH3, HOFFSET(GridsPoints_h5,vH3), mtype_vector3);
        mtype_grids.insertMember( MEMBER_vHe3, HOFFSET(GridsPoints_h5,vHe3), mtype_vector3);
        mtype_grids.insertMember( MEMBER_vO3, HOFFSET(GridsPoints_h5,vO3), mtype_vector3);
        
        mtype_grids.insertMember( MEMBER_density, HOFFSET(GridsPoints_h5,density), PredType::NATIVE_DOUBLE);

        mtype_grids.insertMember( MEMBER_density_H, HOFFSET(GridsPoints_h5,density_H), PredType::NATIVE_DOUBLE);
        mtype_grids.insertMember( MEMBER_density_He, HOFFSET(GridsPoints_h5,density_He), PredType::NATIVE_DOUBLE);
        mtype_grids.insertMember( MEMBER_density_O, HOFFSET(GridsPoints_h5,density_O), PredType::NATIVE_DOUBLE);

    if(h5FileCheck_in == 0)
    {
        H5File* file = new H5File( FILE_NAME, H5F_ACC_TRUNC);

        // print const values at timeline = 0
        DataSet* dataset_const;
        dataset_const = new DataSet(file->createDataSet( DATASET_CONST_NAME, mtype_grids_const, space));
        dataset_const->write( array_data_const[0][0][0], mtype_grids_const);

        delete dataset_const;
        delete data_mem_const;  // notice where is the definition

        delete file;
    }
    else
    {
        H5File* file = new H5File( FILE_NAME, H5F_ACC_RDWR);
  
        DataSet* dataset;
        dataset = new DataSet(file->createDataSet(DATASET_NAME, mtype_grids, space));
        dataset->write( array_data[0][0][0], mtype_grids);

        delete dataset;
        delete data_mem;
        
        delete file;
    }
    
}



//************************************************************************
//************************************************************************
// FUNCTION
// Printout the gridpoints on the girds as hdf5 format
// Step 1: Generate a new matrix fulling with gridspoints class
// Step 2: Print out it as .h5
void PrintOutHdf5_Particles(int timeline, 
                            vector<Particles>& ptrParticlesList_H,
                            vector<Particles>& ptrParticlesList_He,
                            vector<Particles>& ptrParticlesList_O
                            )
{
    using namespace H5;
 /*   
    char filename[80];
    sprintf( filename, "ArrayOfGrids_%d", timeline);
    H5std_string DATASET_NAME( filename);
*/
    H5std_string FILE_NAME( "ParticlesData.h5");
    H5std_string DATASET_NAME_H( "Particles_H");
    H5std_string DATASET_NAME_He( "Particles_He");
    H5std_string DATASET_NAME_O( "Particles_O");

    int numParticle_H = ptrParticlesList_H.size();
    int numParticle_He = ptrParticlesList_He.size();
    int numParticle_O = ptrParticlesList_O.size();

    double* data_mem_particles_H = new double[8*numParticle_H];
    double** array_data_particles_H = new double*[numParticle_H];
    
    double* data_mem_particles_He = new double[8*numParticle_He];
    double** array_data_particles_He = new double*[numParticle_He];
    
    double* data_mem_particles_O = new double[8*numParticle_O];
    double** array_data_particles_O = new double*[numParticle_O];

    int RANK =2;
    hsize_t dimsH[2];
    hsize_t dimsHe[2];
    hsize_t dimsO[2];
    dimsH[0] = numParticle_H;
    dimsH[1] = 8;
    
    dimsHe[0] = numParticle_He;
    dimsHe[1] = 8;
    
    dimsO[0] = numParticle_O;
    dimsO[1] = 8;

    for( int i =0; i< numParticle_H; i ++)
    {
        array_data_particles_H[i] = data_mem_particles_H + 8 * i ;
        array_data_particles_H[i][0] = ptrParticlesList_H[i].PosParticles().x();
        array_data_particles_H[i][1] = ptrParticlesList_H[i].PosParticles().y();
        array_data_particles_H[i][2] = ptrParticlesList_H[i].PosParticles().z();
        array_data_particles_H[i][3] = ptrParticlesList_H[i].VelParticles().x();
        array_data_particles_H[i][4] = ptrParticlesList_H[i].VelParticles().y();
        array_data_particles_H[i][5] = ptrParticlesList_H[i].VelParticles().z();
        array_data_particles_H[i][7] = ptrParticlesList_H[i].WeightNi();
        array_data_particles_H[i][8] = ptrParticlesList_H[i].MagneticIvarient();
    }
    for( int i =0; i< numParticle_He; i ++)
    {
        array_data_particles_He[i] = data_mem_particles_He + 8 * i ;
        array_data_particles_He[i][0] = ptrParticlesList_He[i].PosParticles().x();
        array_data_particles_He[i][1] = ptrParticlesList_He[i].PosParticles().y();
        array_data_particles_He[i][2] = ptrParticlesList_He[i].PosParticles().z();
        array_data_particles_He[i][3] = ptrParticlesList_He[i].VelParticles().x();
        array_data_particles_He[i][4] = ptrParticlesList_He[i].VelParticles().y();
        array_data_particles_He[i][5] = ptrParticlesList_He[i].VelParticles().z();
        array_data_particles_He[i][7] = ptrParticlesList_He[i].WeightNi();
        array_data_particles_He[i][8] = ptrParticlesList_He[i].MagneticIvarient();
    }
    for( int i =0; i< numParticle_O; i ++)
    {
        array_data_particles_O[i] = data_mem_particles_O + 8 * i ;
        array_data_particles_O[i][0] = ptrParticlesList_O[i].PosParticles().x();
        array_data_particles_O[i][1] = ptrParticlesList_O[i].PosParticles().y();
        array_data_particles_O[i][2] = ptrParticlesList_O[i].PosParticles().z();
        array_data_particles_O[i][3] = ptrParticlesList_O[i].VelParticles().x();
        array_data_particles_O[i][4] = ptrParticlesList_O[i].VelParticles().y();
        array_data_particles_O[i][5] = ptrParticlesList_O[i].VelParticles().z();
        array_data_particles_O[i][7] = ptrParticlesList_O[i].WeightNi();
        array_data_particles_O[i][8] = ptrParticlesList_O[i].MagneticIvarient();
    }

        cout << numParticle_H <<  " " << numParticle_He << " " << numParticle_O << endl;
        H5File file_particles( FILE_NAME, H5F_ACC_TRUNC);

        DataSpace dataspace_particles_H = DataSpace( RANK, dimsH);
        DataSet dataset_H;
        dataset_H = file_particles.createDataSet( DATASET_NAME_H, PredType::NATIVE_DOUBLE, dataspace_particles_H);
        dataset_H.write(array_data_particles_H[0], PredType::NATIVE_DOUBLE);
        dataspace_particles_H.close();
        dataset_H.close();

        DataSpace dataspace_particles_He = DataSpace( RANK, dimsHe);
        DataSet dataset_He;
        dataset_He = file_particles.createDataSet( DATASET_NAME_He, PredType::NATIVE_DOUBLE, dataspace_particles_He);
        dataset_He.write(array_data_particles_He[0], PredType::NATIVE_DOUBLE);
        dataspace_particles_He.close();
        dataset_He.close();

        DataSpace dataspace_particles_O = DataSpace( RANK, dimsO);
        DataSet dataset_O;
        dataset_O = file_particles.createDataSet( DATASET_NAME_O, PredType::NATIVE_DOUBLE, dataspace_particles_O);
        dataset_O.write(array_data_particles_O[0], PredType::NATIVE_DOUBLE);
        dataspace_particles_O.close();
        dataset_O.close();

        file_particles.close();

        delete array_data_particles_H;
        delete array_data_particles_He;
        delete array_data_particles_O;
        delete data_mem_particles_H;
        delete data_mem_particles_He;
        delete data_mem_particles_O;


}


//************************************************************************
//************************************************************************
// Read particles
void ReadParticlesVector(   vector<Particles>& ptrParticlesList_H,
                            vector<Particles>& ptrParticlesList_He,
                            vector<Particles>& ptrParticlesList_O,
                            vector<int>& ptrParticlesList_out_H,
                            vector<int>& ptrParticlesList_out_He,
                            vector<int>& ptrParticlesList_out_O
                            )
{
    using namespace H5;
    H5std_string FILE_NAME( "ParticlesData.h5");
    H5std_string DATASET_NAME_H( "Particles_H");
    H5std_string DATASET_NAME_He( "Particles_He");
    H5std_string DATASET_NAME_O( "Particles_O");

    hsize_t dims_read_H[2];
    hsize_t dims_read_He[2];
    hsize_t dims_read_O[2];
    H5File file_particles( FILE_NAME, H5F_ACC_RDWR);

    DataSet dataset_read_H;
    DataSet dataset_read_He;
    DataSet dataset_read_O;
    dataset_read_H = file_particles.openDataSet( DATASET_NAME_H);
    dataset_read_He = file_particles.openDataSet( DATASET_NAME_He);
    dataset_read_O = file_particles.openDataSet( DATASET_NAME_O);

    DataSpace dataspace_read_H = dataset_read_H.getSpace();
    DataSpace dataspace_read_He = dataset_read_He.getSpace();
    DataSpace dataspace_read_O = dataset_read_O.getSpace();

    int ndims_H = dataspace_read_H.getSimpleExtentDims( dims_read_H, NULL);
    int numParticle_H = dims_read_H[0]; //ptrParticlesList_H.size();
    
    int ndims_He = dataspace_read_He.getSimpleExtentDims( dims_read_He, NULL);
    int numParticle_He = dims_read_He[0]; //ptrParticlesList_H.size();
    
    int ndims_O = dataspace_read_O.getSimpleExtentDims( dims_read_O, NULL);
    int numParticle_O = dims_read_O[0]; //ptrParticlesList_H.size();

    // create buf
    double* mem_read_H = new double[numParticle_H * 8];
    double** data_buf_H = new double*[numParticle_H];
    
    double* mem_read_He = new double[numParticle_He * 8];
    double** data_buf_He = new double*[numParticle_He];
    
    double* mem_read_O = new double[numParticle_O * 8];
    double** data_buf_O = new double*[numParticle_O];

    for( int i = 0; i< numParticle_H ; i++)
    {
        data_buf_H[i] = mem_read_H + i * 8;
    }	

    for( int i = 0; i< numParticle_He ; i++)
    {
        data_buf_He[i] = mem_read_He + i * 8;
    }	

    for( int i = 0; i< numParticle_O ; i++)
    {
        data_buf_O[i] = mem_read_O + i * 8;
    }	

    // read
    dataset_read_H.read(data_buf_H[0], PredType::NATIVE_DOUBLE);
    dataset_read_He.read(data_buf_He[0], PredType::NATIVE_DOUBLE);
    dataset_read_O.read(data_buf_O[0], PredType::NATIVE_DOUBLE);

    double px, py, pz;
    double vx, vy, vz;
    double weightNi;
    double mu;   

    uint_64 posUint = 0, face = 0, ip = 0, jp = 0, kp = 0;
    double temp[2];
    Vector3 pos, vel;
    Particles tempP;

    // create array of particles_main and particles_out: H
    for( int i = 0; i < numParticle_H; i++)
    {
        px = data_buf_H[i][0];
        py = data_buf_H[i][1];
        pz = data_buf_H[i][2];
        vx = data_buf_H[i][3];
        vy = data_buf_H[i][4];
        vz = data_buf_H[i][5];
        weightNi = data_buf_H[i][6];
        mu = data_buf_H[i][7];

        double L = sqrt( px*px + py*py + pz*pz )/radius;
        // check if in the main domain
        if( L > LMax_maindomain || L < LMin_maindomain) 
        {
            ptrParticlesList_out_H.push_back( i);
        }    
        kp = static_cast<uint_64>( floor( log10(L / LMin)/logRatio *cellSize1)); 
        // 4.2 XYZtoUV, note that -1<UV<1 
        face = Getface(px, py, pz);
        switch (face)
        {
        case 0: temp[0] = py/px; temp[1] = pz/px; break;
        case 1: temp[0] =-px/py; temp[1] = pz/py; break;
        case 2: temp[0] = py/pz; temp[1] =-px/pz; break;
        case 3: temp[0] = py/px; temp[1] =-pz/px; break;
        case 4: temp[0] =-px/py; temp[1] =-pz/py; break;
        default:temp[0] =-py/pz; temp[1] =-px/pz; break;
        }
        // 4.3 UVtoST, note that 0<ST<1
        for (int i=0; i<=1; i++)
        {
        if (temp[i] >= 0) temp[i] = 0.5 * std::sqrt(1 + 3*temp[i]);
        else            temp[i] = 1 - 0.5 * std::sqrt(1 - 3*temp[i]);
        }
        // 4.4 STtoIpJp
        ip= static_cast<unsigned int>(floor(temp[0] * particlesGridsSize ));
        jp= static_cast<unsigned int>(floor(temp[1] * particlesGridsSize ));
        // 5. F ip jp kp to Uint_64
        posUint = face << 61 ;
        for( int i = 0; i < particlesGridsLevel; i++)
        {
        posUint += (((ip >> particlesGridsLevel-1-i) & 1 )<< 60 - i *3) 
                    + (((jp >> particlesGridsLevel-1-i) & 1 )<< 60-1 - i *3)
                    + (((kp >> particlesGridsLevel-1-i) & 1 )<< 60-2 - i *3) ;
        }
        pos = Vector3( px, py, pz);
        vel = Vector3( vx, vy, vz);
        tempP = Particles( posUint, pos, vel, weightNi, mu);
        ptrParticlesList_H.push_back( tempP);
    }

    // create array of particles_main and particles_out: He
    for( int i = 0; i < numParticle_He; i++)
    {
        px = data_buf_He[i][0];
        py = data_buf_He[i][1];
        pz = data_buf_He[i][2];
        vx = data_buf_He[i][3];
        vy = data_buf_He[i][4];
        vz = data_buf_He[i][5];
        weightNi = data_buf_He[i][6];
        mu = data_buf_He[i][7];

        double L = sqrt( px*px + py*py + pz*pz )/radius;
        // check if in the main domain
        if( L > LMax_maindomain || L < LMin_maindomain) 
        {
            ptrParticlesList_out_He.push_back( i);
        }    
        kp = static_cast<uint_64>( floor( log10(L / LMin)/logRatio *cellSize1)); 
        // 4.2 XYZtoUV, note that -1<UV<1 
        face = Getface(px, py, pz);
        switch (face)
        {
        case 0: temp[0] = py/px; temp[1] = pz/px; break;
        case 1: temp[0] =-px/py; temp[1] = pz/py; break;
        case 2: temp[0] = py/pz; temp[1] =-px/pz; break;
        case 3: temp[0] = py/px; temp[1] =-pz/px; break;
        case 4: temp[0] =-px/py; temp[1] =-pz/py; break;
        default:temp[0] =-py/pz; temp[1] =-px/pz; break;
        }
        // 4.3 UVtoST, note that 0<ST<1
        for (int i=0; i<=1; i++)
        {
        if (temp[i] >= 0) temp[i] = 0.5 * std::sqrt(1 + 3*temp[i]);
        else            temp[i] = 1 - 0.5 * std::sqrt(1 - 3*temp[i]);
        }
        // 4.4 STtoIpJp
        ip= static_cast<unsigned int>(floor(temp[0] * particlesGridsSize ));
        jp= static_cast<unsigned int>(floor(temp[1] * particlesGridsSize ));
        // 5. F ip jp kp to Uint_64
        posUint = face << 61 ;
        for( int i = 0; i < particlesGridsLevel; i++)
        {
        posUint += (((ip >> particlesGridsLevel-1-i) & 1 )<< 60 - i *3) 
                    + (((jp >> particlesGridsLevel-1-i) & 1 )<< 60-1 - i *3)
                    + (((kp >> particlesGridsLevel-1-i) & 1 )<< 60-2 - i *3) ;
        }
        pos = Vector3( px, py, pz);
        vel = Vector3( vx, vy, vz);
        tempP = Particles( posUint, pos, vel, weightNi, mu);
        ptrParticlesList_He.push_back( tempP);
    }
// create array of particles_main and particles_out: He
    for( int i = 0; i < numParticle_O; i++)
    {
        px = data_buf_O[i][0];
        py = data_buf_O[i][1];
        pz = data_buf_O[i][2];
        vx = data_buf_O[i][3];
        vy = data_buf_O[i][4];
        vz = data_buf_O[i][5];
        weightNi = data_buf_O[i][6];
        mu = data_buf_O[i][7];

        double L = sqrt( px*px + py*py + pz*pz )/radius;
        // check if in the main domain
        if( L > LMax_maindomain || L < LMin_maindomain) 
        {
            ptrParticlesList_out_O.push_back( i);
        }    
        kp = static_cast<uint_64>( floor( log10(L / LMin)/logRatio *cellSize1)); 
        // 4.2 XYZtoUV, note that -1<UV<1 
        face = Getface(px, py, pz);
        switch (face)
        {
        case 0: temp[0] = py/px; temp[1] = pz/px; break;
        case 1: temp[0] =-px/py; temp[1] = pz/py; break;
        case 2: temp[0] = py/pz; temp[1] =-px/pz; break;
        case 3: temp[0] = py/px; temp[1] =-pz/px; break;
        case 4: temp[0] =-px/py; temp[1] =-pz/py; break;
        default:temp[0] =-py/pz; temp[1] =-px/pz; break;
        }
        // 4.3 UVtoST, note that 0<ST<1
        for (int i=0; i<=1; i++)
        {
        if (temp[i] >= 0) temp[i] = 0.5 * std::sqrt(1 + 3*temp[i]);
        else            temp[i] = 1 - 0.5 * std::sqrt(1 - 3*temp[i]);
        }
        // 4.4 STtoIpJp
        ip= static_cast<unsigned int>(floor(temp[0] * particlesGridsSize ));
        jp= static_cast<unsigned int>(floor(temp[1] * particlesGridsSize ));
        // 5. F ip jp kp to Uint_64
        posUint = face << 61 ;
        for( int i = 0; i < particlesGridsLevel; i++)
        {
        posUint += (((ip >> particlesGridsLevel-1-i) & 1 )<< 60 - i *3) 
                    + (((jp >> particlesGridsLevel-1-i) & 1 )<< 60-1 - i *3)
                    + (((kp >> particlesGridsLevel-1-i) & 1 )<< 60-2 - i *3) ;
        }
        pos = Vector3( px, py, pz);
        vel = Vector3( vx, vy, vz);
        tempP = Particles( posUint, pos, vel, weightNi, mu);
        ptrParticlesList_O.push_back( tempP);
    }

 //   delete file_particles;
    delete mem_read_H;
    delete data_buf_H;
    delete mem_read_He;
    delete data_buf_He;
    delete mem_read_O;
    delete data_buf_O;
    
    
}

//************************************************************************
//************************************************************************
// FUNCTION
// Create a array to store volume of cells needed to calculate density 
// at each grids points 
// The volume means the sum volume of adjacent 6 or 8 cells
// Only consider the main domain so that the size is (fieldsGridsSize+1)*(fieldsGridsSize+1)*(fieldsGridsSize+1)
double*** VolumeGridsField( double*** ptrVolumeCellArray_in)
{
    static double* mem_VolumeGridsArray = new double[(fieldsGridsSize+1)*(fieldsGridsSize+1)*(fieldsGridsSize+1)]; 
    double*** VolumeGridsArray = new double **[fieldsGridsSize+1];

    for( int i =0; i < fieldsGridsSize+1; i++)
    {
        VolumeGridsArray[i] = new double*[fieldsGridsSize+1];
        for( int j =0; j < fieldsGridsSize+1; j++)
        {
//            VolumeGridsArray[i][j]= new double [fieldsGridsSize+1];
            VolumeGridsArray[i][j]= mem_VolumeGridsArray + i* (fieldsGridsSize+1)*(fieldsGridsSize+1) + j*(fieldsGridsSize+1);
            for( int k = 0; k < fieldsGridsSize+1; k++)
            {
                if( k == 0 || k == fieldsGridsSize)
                {
                    VolumeGridsArray[i][j][k] = 999.99; // should not be used
                }
                else
                {
                    if( i ==0 && j == 0) { VolumeGridsArray[i][j][k] = 3* ptrVolumeCellArray_in[i+1][j+1][k] + 3* ptrVolumeCellArray_in[i+1][j+1][k+1]; }

                    else if( i ==0 && j ==fieldsGridsSize) { VolumeGridsArray[i][j][k] = 3* ptrVolumeCellArray_in[i+1][j][k] + 3* ptrVolumeCellArray_in[i+1][j][k+1];}
  
                    else if( i ==fieldsGridsSize && j ==0) { VolumeGridsArray[i][j][k] = 3* ptrVolumeCellArray_in[i][j+1][k] + 3* ptrVolumeCellArray_in[i][j+1][k+1];}
     
                    else if( i ==fieldsGridsSize && j ==fieldsGridsSize) { VolumeGridsArray[i][j][k] = 3* ptrVolumeCellArray_in[i][j][k] + 3* ptrVolumeCellArray_in[i][j][k+1];}
              
                    else if( i ==0 && j !=0 && j != fieldsGridsSize) { VolumeGridsArray[i][j][k] = 2* ptrVolumeCellArray_in[i+1][j+1][k] + 2* ptrVolumeCellArray_in[i+1][j][k]
                                                                        + 2* ptrVolumeCellArray_in[i+1][j+1][k+1] + 2* ptrVolumeCellArray_in[i+1][j][k+1];}

                    else if( i ==fieldsGridsSize && j !=0 && j!= fieldsGridsSize) { VolumeGridsArray[i][j][k] = 2* ptrVolumeCellArray_in[i][j+1][k] + 2* ptrVolumeCellArray_in[i][j][k]
                                                                                     + 2* ptrVolumeCellArray_in[i][j+1][k+1] + 2* ptrVolumeCellArray_in[i][j][k+1];}

                    else if( j ==0 && i != 0 && i != fieldsGridsSize) { VolumeGridsArray[i][j][k] = 2* ptrVolumeCellArray_in[i+1][j+1][k] + 2* ptrVolumeCellArray_in[i][j+1][k]
                                                                                                    + 2* ptrVolumeCellArray_in[i+1][j+1][k+1] + 2* ptrVolumeCellArray_in[i][j+1][k];}

                    else if( j ==fieldsGridsSize && i != 0 && i != fieldsGridsSize) { VolumeGridsArray[i][j][k] = 2* ptrVolumeCellArray_in[i+1][j][k] + 2* ptrVolumeCellArray_in[i][j][k]
                                                                                                    + 2* ptrVolumeCellArray_in[i+1][j][k+1] + 2* ptrVolumeCellArray_in[i][j][k+1];}

                    else 
                    {
                        VolumeGridsArray[i][j][k] = ptrVolumeCellArray_in[i+1][j+1][k] + ptrVolumeCellArray_in[i][j+1][k] + ptrVolumeCellArray_in[i+1][j][k] + ptrVolumeCellArray_in[i][j][k] 
                                                  + ptrVolumeCellArray_in[i+1][j+1][k+1] + ptrVolumeCellArray_in[i][j+1][k+1] + ptrVolumeCellArray_in[i+1][j][k+1] + ptrVolumeCellArray_in[i][j][k+1];                        
                    }
                }
            }
        }
    }
    
    return VolumeGridsArray;
}


//************************************************************************
//************************************************************************
// FUNCTION
// Create a array to store volume of cells needed to calculate density 
// at each cell [fieldsize+2][fieldsize+2][fieldsize]
double*** VolumeCellsField( GridsPoints***** ptrArray_in)
{
    static double* mem_VolumeCellsArray = new double[(fieldsGridsSize+2) * (fieldsGridsSize+2) * (fieldsGridsSize)];
    double*** VolumeCellsArray = new double**[fieldsGridsSize+2];
    for( int i = 0; i < fieldsGridsSize+2; i++)
    {
        VolumeCellsArray[i] = new double*[fieldsGridsSize+2];
        for( int j = 0; j < fieldsGridsSize+2; j++)
        {         
//            VolumeCellsArray[i][j] = new double[fieldsGridsSize];
            VolumeCellsArray[i][j] = mem_VolumeCellsArray + i* (fieldsGridsSize)* (fieldsGridsSize+2) 
                                     + j* (fieldsGridsSize);
            for( int k = 0; k< fieldsGridsSize; k++)
            {
                VolumeCellsArray[i][j][k] = CellVolume( ptrArray_in, 0, i, j, k);
            /*  if( VolumeCellsArray[i][j][k] == 0){
                std::cout << i << " " << j << " " << k << std::endl;
                std::cout << VolumeCellsArray[i][j][k] << std::endl;
                }
            */
            }
        }
    }
    return VolumeCellsArray;
}




//************************************************************************
//************************************************************************
// FUNCTION
// Calculation the temprature
void Titheridge_Te( GridsPoints***** ptrArray_in) 
//  by Yuzhang Ma AUG 16,2019
{
//inputs
double  SEC = 18*3600; // second of day
double  DOY = 31;      // day of year

double  Kp   = 10;
double  F107 = 100;

//  consts
const double rad2deg = 57.2957763671875;
const double pi = 3.1415927410125732;
const double PLAT=1.37846; //geographic latitude (rad) of Earth's north magnetic pole
const double PLON=5.04557; //geographic longitude (rad) of Earth's north magnetic pole
const double h0 = 400.0e0,     R0 = 1.0627825e0,R02 = 1.1295067e0;
const double por = 0.2857142e0,Re = 6371.2e0,   x1 = 1.0470869e0;
const double a0 = 1.23e3,a1 = 2.2e3,  a2 = -3.29e3,a3 = -2.6e-1,a4 = -6.8e-1;
const double b0 = 4.65e0,b1 = -8.55e0,b2 = 4.14e0, b3 = -2.16e0,b4 = 1.45e0;
const double aa0 = 9.85e2, aa1 = -9.63e2,aa2 = 1.125e3,aa3 = -0.6e0,aa4 = 0.10e0; 
const double bb0 = 7.56e-1,bb1 = -8.8e-1,bb2 = 2.9e-1,bb3 = -2.63e0,bb4 = 1.84e0;

double  GLONR=15.0*(12.0-SEC/3600.0)/rad2deg;//GLONR in rad

        if(GLONR < 0.0) 
		{  
	    GLONR += 2.0*pi; // GLONR = GLONR + 2*pi
		}
		if(GLONR > 2.0*pi) 
		{  
	    GLONR -= 2.0*pi; // GLONR = GLONR - 2*pi
		}

double  MLON12=atan(sin(PLAT)*tan(GLONR-PLON));

        if(MLON12 < 0.0)
		{
	    MLON12+=2.0*pi; // MLON12 = MLON12 + 2*pi
	    }		  

//		  
//  caution: Px_in py_in pz_in should be transformed to SM Coordinate before using. 
//

   
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 0; k < fieldsGridsSize+1; k++)
                { 
                    
                    //check stopsign
                    if( ptrArray_in[face][i][j][k]->StopSign() == 1) continue;

                    double px_in = ptrArray_in[face][i][j][k]->Pos3().x();
                    double py_in = ptrArray_in[face][i][j][k]->Pos3().y();
                    double pz_in = ptrArray_in[face][i][j][k]->Pos3().z();

    //    std::cout << face << i<<j<< k<< " --> ";
    //    std::cout << px_in << " " << py_in << " " << pz_in << " A--> ";
        
                    double  rr=ptrArray_in[face][i][j][k]->Pos3().norm(); // in unit of m
                    double  Lat= asin( pz_in / rr);	
                    double  phi=atan(py_in/px_in);    
                    double  L= rr/ pow(cos( Lat), 2.0);  
                    double  heq=(L-1.0e0)*Re;	
                    double  SL=1.0e0-x1/L;
                    double  BLATD=asin(sqrt(SL))*rad2deg; // BLATD in degree geomagnetic latitude at 300km       
                    double  BLOND=(phi+MLON12)*rad2deg;// BLOND in degree // NaN for polar points

        // std::cout << phi << " " << BLATD << " " << BLOND << " B==> ";

                    //GLAT calculate
                    double  BLONR=BLOND/rad2deg;
                    double  BLATR=BLATD/rad2deg;
                    double  XM=cos(BLATR)*cos(BLONR);
                    double  ZM=sin(BLATR);
                    double  XG=XM*sin(PLAT)+ZM*cos(PLAT);
                    double  ZG=-XM*cos(PLAT)+ZM*sin(PLAT);
                    double	GLATD=asin(ZG)*rad2deg;// GLATD in degree
                    double  GLATR=GLATD/rad2deg;
                    //  day time T0 and G0  Eq.(19) in Titheridge, JGR1998
                    double  T0d=(a0+a1*SL+a2*SL*SL)/(1.0e0+a3*SL+a4*SL*SL);
                    double  G0d=(b0+b1*SL+b2*SL*SL)/(1.0e0+b3*SL+b4*SL*SL);
    
                    //  night time T0 and G0
                    double  T0n=(aa0+aa1*SL+aa2*SL*SL)/(1.0e0+aa3*SL+aa4*SL*SL);
                    double  G0n=(bb0+bb1*SL+bb2*SL*SL)/(1.0e0+bb3*SL+bb4*SL*SL);

                    //  change in solar activity
                    double  delta_T0=3.4*(F107-120.0);
                    G0d=G0d*T0d/(T0d+delta_T0);
                    T0d=T0d+delta_T0;
                    G0n=G0n*T0n/(T0n+delta_T0);
                    T0n=T0n+delta_T0;
                    //  change in magnetic activity
                    if(BLATD > 46.0e0)		  
                    {
                        double  z=0.135*(BLATD-46.0)/rad2deg;
                        double  Dk=37.0+1.33*(BLATD-46.0)-37.0*cos(z);
                        delta_T0=Dk*(Kp-1.5);
                        G0d=G0d*pow(T0d/(T0d+delta_T0),2.5);
                        T0d=T0d+delta_T0;
                        G0n=G0n*pow(T0n/(T0n+delta_T0),2.5);
                        T0n=T0n+delta_T0;
		            }	  

                    double  G0T0d=G0d/T0d;
                    double  G0T0n=G0n/T0n;

                    double alt=(rr / 1000 / Re -1)*Re;
                    double alg=log(alt/h0);
                    double R2=pow(1.0e0+alt/Re,2.0);
                    double Bh=0.05e0/(2.0e0*L-R0)*(88.0e0+alg*(10.5e0-alg));

       // std::cout << T0d << " " << Bh << " " << G0T0d << " " << G0T0n << " heq " << heq << " alt " << alt << " C==> ";
                    //  mean day values from Eq.(13) in Titheridge, 1998 JGR 
                    double Tday0=T0d*pow(1.0e0+Bh*G0T0d*((heq-h0)/R02-(heq-alt)/R2),por);
                    //  mean night values from Eq.(13) in Titheridge, 1998 JGR 
                    double Tnig0=T0n*pow(1.0e0+Bh*G0T0n*((heq-h0)/R02-(heq-alt)/R2),por);


      //  std::cout << Tnig0 << " " << Tday0 << " D==> ";
                    //  local solar time (SAT) inputs: day of year,GLONR,local time
                    //  https://pvcdrom.pveducation.org/SUNLIGHT/SOLART.HTM
                    double B=300/365*(DOY-81)/rad2deg; //B is degree; trans to rad
                    double EOT=9.87*sin(2*B)-7.53*cos(B)-1.5*sin(B);
                    // get the time difference form GLONR 
                    // https://blog.csdn.net/fct2001140269/article/details/86513925
                    int	currentLon=GLONR*rad2deg;
                    if (currentLon>180)
                    {
	                    currentLon=-1*(360-currentLon);
                    }
                    int timeZone;
                    int shangValue = (int) (currentLon / 15);
                    double yushuValue = abs(currentLon % 15);
                    if (yushuValue <= 7.5) 
		            {
                        timeZone = shangValue;
                    } else 
		            {
                        timeZone = shangValue + (currentLon > 0 ? 1 : -1);
                    }
                    double LSTM=15*timeZone;
                    double TC=4*(LSTM-GLONR*rad2deg)+EOT;
                    double SAT=SEC/3600+TC/60;
                    if (SAT < 0) {SAT+=24.0;}
	                if (SAT > 24.0) {SAT-=24.0;}
                    //DEC -- solar declination angle in radians
                    //solar declination angle inputs: day of year, output is in dgree, trans to rad)
                    //https://www.sciencedirect.com/topics/engineering/solar-declination
                    double DEC=23.45*sin(360/365*(284+DOY))/rad2deg;
                    double S_LONG=-1.0e0*tan(GLATR)*tan(DEC);
                    double s_r;
                    if(S_LONG >= -1.0e0 && S_LONG <= 1.0e0)
	                {
		                s_r=12.0e0-3.82*acos(S_LONG);
		            }
	                else
		            { 
                        if(S_LONG<=-1.0e0){s_r=0.0e0;}
                        else{s_r=12.0e0;}
	                }


                    //duration of the day-night transition 
                    double Delta_tr=1.2+0.5*SL;
                    double Delta_ts=Delta_tr+0.9;
                    //time of the center of the transition in hours after ground sunrise or sunset
                    double  t_s=0.15*s_r;
                    if(t_s >= 1.0e0){t_s=1.0;}
                    double  t_r=-0.5*t_s;
                    double  D;      
                    if(SAT<=12.0e0)
		            {D=(s_r-0.5*t_s-SAT)/Delta_tr;}
                    else
		            {D=(SAT-t_s+s_r-24.0e0)/Delta_ts;}
                    phi=1.0/(1.0+exp(3.2*D));
                    double  y=s_r-12.5;
                    if(y<=-4.0){y=-4.0;}
                    double  TDvar=0.97+0.22*pow((SAT-12.5)/y,2);
                    double  Tday;        
                    if(TDvar<=1.2)
		            {Tday=TDvar*Tday0;}
                    else
		            {Tday=1.2*Tday0;}
        
                    if(SAT<=12.0e0)
		            {y=SAT;}
                    else
                    {y=SAT-24.0;}
                    double  TNvar=0.83+0.15*exp(-0.2*y*(1.4-0.8*SL));
                    double  Tnig;       
                    if(TNvar<=1.2)
		            {Tnig=TNvar*Tnig0;}
                    else
                    {Tnig=1.2*Tnig0;}
         
                    double  Te=Tnig+(Tday-Tnig)*phi;// should be the avrage value of 2 Te points,it could be done out of the function

       // std::cout << Te << std::endl;

                    ptrArray_in[face][i][j][k]->SetTemperature(Te);
                    
                    // set stopSign
                    ptrArray_in[face][i][j][k]->SetStopSign(1);
                }
            }
        }
    }

    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 0; k < fieldsGridsSize+1; k++)
                {           
                    // set stopSign  
                    ptrArray_in[face][i][j][k]->SetStopSign(0);
                }
            }
        }
    }    

}


//************************************************************************
//************************************************************************
// Function
// initial the bot boundary for the  velocity of magnetic field line
void SetRotationalVelBotBoundary( GridsPoints***** ptrArray_in, int timeline_in)
{
    double PI = 3.1415926535897;
    // Set the dawn and equatorial point as zero point
    
    std::cout << " Set Bot boundary " << std::endl;
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 0; k < tempGridsCellLevel+1; k++)
                {
                if( ptrArray_in[face][i][j][k]->StopSign() == 1) continue;

                double x = ptrArray_in[face][i][j][k]->Pos3().x();
                double y = ptrArray_in[face][i][j][k]->Pos3().y();
                double z = ptrArray_in[face][i][j][k]->Pos3().z();

                //Set density
                double longtitude;
                double latitude;

                double A = 0.5 * ( rho_max - rho_min);
                double A_average = 0.5 * ( rho_max + rho_min);
                double rho;

                if( x == 0 && y == 0)
                { rho = A_average;}
                else if( x == 0 && y > 0)
                { longtitude = PI / 2.0;}
                else if( x == 0 && y < 0)
                { longtitude = PI / 2.0 * 3.0;}
                else if( x!= 0)
                {
                
                longtitude = atan( y / x);

                if( x<0) { longtitude = longtitude + PI;}

                }

                latitude = PI / 2.0 - acos( z / sqrt( x*x + y*y + z*z));   
 
                double r = ptrArray_in[face][i][j][k]->Pos3().norm() / radius;
                double parameter = 0.5 * ( 1.0 - tanh( r - 6.5)) / r;
                
//                rho = ( A - 2.0 * A / PI * abs( latitude)) * sin( longtitude) + A_average;
                rho = ( A - 2.0 * A / PI * abs( latitude)) * sin( longtitude + PI / 2.0) / pow(r, 6.0) + A_average;
               
                ptrArray_in[face][i][j][k]->Density_H( rho * ratioH / mi0_H * parameter);
                ptrArray_in[face][i][j][k]->Density_He( rho * ratioHe / mi0_He * parameter);
                ptrArray_in[face][i][j][k]->Density_O( rho * ratioO / mi0_O * parameter);
              
                // set velocity
                SetRotationalVel(ptrArray_in, face, i, j, k);
                Vector3 original_vel = ptrArray_in[face][i][j][k]->Vel3();
                ptrArray_in[face][i][j][k]->SetVel_Boundary(original_vel.ScaleProduct(sin(PI/2.0*(timeline_in*tstep-botBoundaryInitialTimeStart)/botBoundaryInitialTime)));

                // set E
                Vector3 temp_gradPe = Vector3( 0.0, 0.0, 0.0);
                ptrArray_in[face][i][j][k]->updateE( temp_gradPe);

                ptrArray_in[face][i][j][k]->SetStopSign(1);
                }
            }
        }
    }

    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 0; k < tempGridsCellLevel+1; k++)
                {
                // set stopSign  
                ptrArray_in[face][i][j][k]->SetStopSign(0);
                }
            }
        }
    } 

}


//************************************************************************
//************************************************************************
// Function
// initial the top boundary for the  velocity of magnetic field line
void SetConvectionVelTopBoundary( GridsPoints***** ptrArray_in, int timeline_in)
{
    double PI = 3.1415926535897;
    // input two const
    double r0 = radius * cos( r0_latitude * PI / 180.0);
    double c0 = radius * cos( c0_latitude * PI / 180.0);
    double t0 = t0_convection;
    double r_earth = radius;

    std::cout << " Set Top boundary " << std::endl;
    //non-circle
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                int k = fieldsGridsSize;
                
                if( ptrArray_in[face][i][j][k]->StopSign() == 1) continue;
                SetConvectionVel(ptrArray_in, face, i, j, k);
                Vector3 original_vel = ptrArray_in[face][i][j][k]->Vel3();
                ptrArray_in[face][i][j][k]->SetVel_Boundary(original_vel.ScaleProduct(sin(PI/2.0*(timeline_in*tstep-topBoundaryInitialTimeStart)/topBoundaryInitialTime)));

                double r = ptrArray_in[face][i][j][k]->Pos3().norm() / radius;
                if( r > 0){
                ptrArray_in[face][i][j][k]->Density_H( N0_H / r * ( 1.0 - tanh( r - 6.5)));

                ptrArray_in[face][i][j][k]->Density_He( N0_He / r * ( 1.0 - tanh( r - 6.5)));

                ptrArray_in[face][i][j][k]->Density_O( N0_O / r * ( 1.0 - tanh( r - 6.5)));   
                
                }
                // set E
                Vector3 temp_gradPe = Vector3( 0.0, 0.0, 0.0);
                ptrArray_in[face][i][j][k]->updateE( temp_gradPe);

                // set stopSign
                ptrArray_in[face][i][j][k]->SetStopSign(1);
        
            }
        }
    }

    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                int k = fieldsGridsSize;

                // set stopSign  
                ptrArray_in[face][i][j][k]->SetStopSign(0);
            }
        }
    } 

}



//************************************************************************
//************************************************************************
// Function
// Set initial condition
void SetInitialCondition( GridsPoints***** ptrArray_in, Vector3*** ptrVectorCellArray_in, double*** ptrVolumeCellArray_in)
{
    double PI = 3.1415926535897;

    
    for( int face = 0; face < totalFace; face++)
    {
    if( update_type == 0)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 0; k < fieldsGridsSize+1; k++)
                {
                    // Set velocity
                    SetConvectionVel( ptrArray_in, face, i, j, k);

                }
            }
        }
    }
        // Set E3 from k=1 to k=fieldsgridsize-1
        ptrVectorCellArray_in = ValueGradient( ptrVectorCellArray_in, ptrVolumeCellArray_in, ptrArray_in, face, 'P');
        UpdateE3( ptrVectorCellArray_in, ptrArray_in, face);
        // Set E3 for k=0 and k=fieldsgridsize
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                int k = 0;
                ptrArray_in[face][i][j][k]->SetE3(ptrArray_in[face][i][j][k+1]->E3());
                /*
                Vector3 temp_gradPe = ptrArray_in[face][i][j][k]->Pos3().NormalizedVector().ScaleProduct( (ptrArray_in[face][i][j][k+1]->Density() * ptrArray_in[face][i][j][k+1]->Temperature() -
                                        ptrArray_in[face][i][j][k]->Density() * ptrArray_in[face][i][j][k]->Temperature()) * boltzmann_k 
                                        / (ptrArray_in[face][i][j][k+1]->Pos3().norm() - ptrArray_in[face][i][j][k]->Pos3().norm())) ;
                ptrArray_in[face][i][j][k]->updateE( temp_gradPe);
                */                
                k = fieldsGridsSize;
                ptrArray_in[face][i][j][k]->SetE3(ptrArray_in[face][i][j][k-1]->E3());
                /*
                temp_gradPe = ptrArray_in[face][i][j][k]->Pos3().NormalizedVector().ScaleProduct( (ptrArray_in[face][i][j][k+1]->Density() * ptrArray_in[face][i][j][k+1]->Temperature() -
                                        ptrArray_in[face][i][j][k]->Density() * ptrArray_in[face][i][j][k]->Temperature()) * boltzmann_k 
                                        / (ptrArray_in[face][i][j][k+1]->Pos3().norm() - ptrArray_in[face][i][j][k]->Pos3().norm())) ;
                ptrArray_in[face][i][j][fieldsGridsSize]->updateE( temp_gradPe);
                */
            }
        }

    }
}

//************************************************************************
//************************************************************************
// Function
// Set velocity due to earth rotation
void SetRotationalVel( GridsPoints***** ptrArray_in, int face_in, int i_in, int j_in, int k_in)
{
    Vector3 tempPos = ptrArray_in[face_in][i_in][j_in][k_in]->Pos3();
    Vector3 tempOmega = Vector3( 0.0, 0.0, omega_earth);
    tempPos.Setz( 0.0);
    ptrArray_in[face_in][i_in][j_in][k_in]->SetVel_Boundary( tempOmega.CrossProduct(tempPos));
}

//************************************************************************
//************************************************************************
// Function
// Set velocity due to two convection cell patern
void SetConvectionVel( GridsPoints***** ptrArray_in, int face_in, int i_in, int j_in, int k_in)
{
    
    double PI = 3.1415926535897;
    // input two const
    double r0 = radius * cos( r0_latitude * PI / 180.0);
    double c0 = radius * cos( c0_latitude * PI / 180.0);
    double t0 = t0_convection;
    double r_earth = radius;

    double x = ptrArray_in[face_in][i_in][j_in][k_in]->Pos3().x();
    double y = ptrArray_in[face_in][i_in][j_in][k_in]->Pos3().y();
    double z = ptrArray_in[face_in][i_in][j_in][k_in]->Pos3().z();

    // Set velocity
    double r_top = sqrt( x * x + y * y + z * z);
    double theta_top = acos( z / r_top); 
    double phi_top;
    if( x != 0.0)
    {
        phi_top = atan( y/x );
        if( x < 0) 
        {
            phi_top = phi_top + PI;
        }
    }
    else if ( x == 0.0 && y > 0.0)
    {
        phi_top = PI / 2.0;
    }
    else if ( x == 0.0 && y < 0.0)
    {
        phi_top = PI / 2.0 * ( - 1.0);
    }
    else if ( x ==0.0 && y == 0.0)
    {
        phi_top = 0.0; // special points
    }

   
    // Step 1
    // find related point on the earth shell in the north
    double theta_earth = asin( sin( theta_top) * sqrt( r_earth / r_top));
    double phi_earth = phi_top;
    double x_earth = r_earth * sin( theta_earth) * cos(phi_earth);
    double y_earth = r_earth * sin( theta_earth) * sin(phi_earth);
    double z_earth = r_earth * cos( theta_earth);

    if( x==0.0 && y == 0.0)
    {
        x_earth = 0.0;
        y_earth = 0.0;
    }
//????????????????????????
    // Step 2
    // find the velocity of the point ( |x_earth|, y_earth) on the x-y plane
    double xx = x_earth;
    double yy = y_earth;
    double vx_earth = 0.0;
    double vy_earth = 0.0;
    double L;   // distance, half of period for sin function

// cout << xx << " " << yy << " " << r0 << endl;

    double x_prime, y_prime;    // used for region 2
    if( y_earth < 0.0) 
    {
        yy = -1.0 * yy;
    }
    if( xx <= r0 - r0 *yy / c0 && xx >= -1.0 * r0 + yy * r0 / c0)       // region 1
    {
    //    cout << " test 1 " << endl;
        L = 2.0 * r0 * ( 1.0 - yy / c0);
        vx_earth = -1.0 * PI * L / t0 * sqrt( 0.25 - xx*xx / L / L);
        vy_earth = 0.0;

    }
    else if( xx *xx + yy* yy <= r0 * r0) // region 2
    {
    //    cout << " test 2 " << endl;
        y_prime = ( yy - r0*r0/c0 + sqrt( (yy-r0*r0/c0)*(yy-r0*r0/c0) - (r0*r0/c0/c0 -1.0)*(r0*r0-xx*xx-yy*yy))) / (1.0 - r0*r0/c0/c0);
        x_prime = r0 * ( 1.0- y_prime / c0);
        
        L = 2.0 * x_prime;  // x direction
        if( L != 0.0 && xx < x_prime - 1e-6)
        {
            vx_earth = PI * L / t0 * sqrt( 0.25 - xx * xx / L / L);
        } else
        {
            vx_earth = 0.0;
        }

        L = x_prime; // y direction
        if( L != 0.0 && (yy- y_prime) / L < 1.0 - 1e-6)
        {
            vy_earth = PI * L / t0 * sqrt( (yy - y_prime) / L * ( 1.0 - ( yy - y_prime) / L));

        } else
        {
            vy_earth = 0.0;
        }
        
        if( xx > 0.0)
        {
            vy_earth = -1.0 * vy_earth;
        }


    }
    else // other places
    {
//        cout << " test 3 " << endl;
        vx_earth = 0.0;
        vy_earth = 0.0;
    }
    if( y_earth < 0.0) 
    {
       vy_earth *= -1.0 ;
    }

/*
    // Rotate for a x-axis pointed to the sun
    double vx_earth_rotate = vy_earth;
    double vy_earth_rotate = vx_earth;
    vx_earth = vx_earth_rotate;
    vy_earth = vy_earth_rotate; 
*/
// cout << vx_earth << " " << vy_earth << " >> " << endl;
/*    if( k_in == 16 && i_in == fieldsGridsSize/2 +1 &&  j_in == 5 && face_in == 5) {
    cout << face_in << " " << i_in << " " << j_in << " " << k_in << " vel_earth " << vx_earth << " " << vy_earth <<
     " pos " << x << " " << y << " " << z << endl;}
 */
    // Step 3
    // find the realted velocity on the earth ( x_earth, y_earth, z_earth) or ( r_earth, theta_earth, phi_earth)
    // the velocity on the x and y direction is known as ( vx_earth, vy_earth)
    // Notice the polar points have phi_earth = 0 which is incorrect to use general form or vtheta_earth will be zero

    double vtheta_earth = (vx_earth * cos( phi_earth) + vy_earth * sin( phi_earth)) / cos( theta_earth);
    double vphi_earth = vy_earth * cos( phi_earth) - vx_earth * sin( phi_earth); // notice polar points
    if( theta_earth <= 1e-5)
    {
        vtheta_earth = vx_earth;
    }

// cout << " vtheta_earth " << vtheta_earth << " vphi_earth " << vphi_earth ; // vx_earth & vy_earth are zero

       // Step 4
    // find the related velocity on the arbitrary shell as we want using the equation A21 and A22 of 
    // Rasmussen et.al 1992
    double sinchi_top = 2.0 * cos( theta_top) / sqrt( 1.0+ 3.0* cos( theta_top)* cos( theta_top));
    double coschi_top = sin( theta_top) / sqrt( 1.0 + 3.0* cos( theta_top)* cos( theta_top));

    double vr_top, vtheta_top, vphi_top;
    if ( theta_earth > 1e-5)
    {
    vr_top = r_top * coschi_top * coschi_top * vtheta_earth / r_earth * 2.0 * cos(theta_earth) / sin( theta_earth);
    vtheta_top = r_top * sinchi_top * coschi_top * vtheta_earth / r_earth * 2.0 * cos(theta_earth) / sin( theta_earth); 
    vphi_top = vphi_earth / r_earth  * r_top ;
    } else
    {
        vr_top = 0.0;
        vtheta_top = r_top * vtheta_earth / r_earth;
        vphi_top = 0.0;
    }
    
/*    
    if( k_in == 16 && i_in == fieldsGridsSize/2 +1 &&  j_in == 5 && face_in == 5) {
    cout << face_in << " " << i_in << " " << j_in << " " << k_in << " vr_top " << vr_top << " vtheta_top " << vtheta_top << " vphi_top " << vphi_top << " " <<
     " pos " << x << " " << y << " " << z << endl;}
*/
//  cout << " vr_top " << vr_top << " vtheta_top " << vtheta_top << " vphi_top " << vphi_top << " >>>> " << endl; //

    double vx_top = vr_top * sin( theta_top) * cos( phi_top) + 
                    vtheta_top * cos(theta_top) * cos( phi_top) -
                    vphi_top * sin(phi_top);
    double vy_top = vr_top * sin( theta_top) * sin(phi_top) +
                    vtheta_top * cos(theta_top) * sin(phi_top) +
                    vphi_top * cos(phi_top);
    double vz_top = vr_top * cos( theta_top) -
                    vtheta_top* sin(theta_top);

    if( theta_earth <= 1e-5)
    {
        vx_top = vtheta_top;
        vy_top = 0.0;
        vz_top = 0.0;
    }
/*
//  cout << " r_top " << r_top << " theta_top " << theta_top << " >>> "; // vtheta_earth is zero
if( k_in == 16 && j_in == fieldsGridsSize / 2 && face_in == 5 )
{
    cout <<endl<< face_in << " " << i_in << " " << j_in << " " << k_in << endl;
    cout << vx_earth << " " << vy_earth << " theta " << theta_earth << " " << theta_top << " phi " << phi_earth << " " << phi_top
    << " phi_top " << phi_top << " vtheta " << vtheta_earth << " vr " << vr_top* sin(theta_top) << " vphi_top " << vphi_top
    << " v_top " << vx_top << " " << vy_top << " " << vz_top << endl;//
}
*/

// cout << vx_top << " " << vy_top << " " << vz_top << endl;
    Vector3 temp = Vector3( vx_top, vy_top, vz_top);
    Vector3 original_vel = ptrArray_in[face_in][i_in][j_in][k_in]->Vel3();
    ptrArray_in[face_in][i_in][j_in][k_in]->SetVel_Boundary( original_vel.PlusProduct( temp));
/*
    if( k_in == 16 && i_in == fieldsGridsSize/2 +1 &&  j_in == 5 && face_in == 5) {
    cout << face_in << " " << i_in << " " << j_in << " " << k_in << " vel " << vx_top << " " << vy_top << " " << vz_top << " " <<
     " pos " << x << " " << y << " " << z << endl;}
*/
}


//************************************************************************
//************************************************************************
// FUNCTION
// Calculate the gradient of normal of B
void GradBNorm( GridsPoints***** ptrArray_in)
{

    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 0; k < fieldsGridsSize+1; k++)
                { 

                    //check stopsign
                    if( ptrArray_in[face][i][j][k]->StopSign() == 1) continue;
                    
                    ptrArray_in[face][i][j][k]->XYZtoGradBNorm();

                    // set stopSigns
                    ptrArray_in[face][i][j][k]->SetStopSign(1);
                }
            }
        }
    }

    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 1; k < fieldsGridsSize; k++)
                {           
                    // set stopSign
                    ptrArray_in[face][i][j][k]->SetStopSign(0);
                }
            }
        }
    }    
}


//************************************************************************
//************************************************************************
// FUNCTION
// Set zero for pho and v at each points
void  ResetPhoVatGrids( GridsPoints***** ptrArray_in)
{
    // reset, clear the previous value: density and velocity
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 1 + tempGridsCellLevel; k < fieldsGridsSize - tempGridsCellLevel; k++)
                {  
                    ptrArray_in[face][i][j][k]->ResetParameters();
                }
            }
        }
    }
}


//************************************************************************
//************************************************************************
// FUNCTION
// finish culmulating pho and velocity and then average the density and velocity
void CalculatingAveragedPhoVatGrids(GridsPoints***** ptrArray_in, 
                                    GridsPoints***** ptrArray_bot, 
                                    GridsPoints***** ptrArray_top, 
                                    double*** ptrVolumeGridArray_in,
                                    int updateInfoPeriod_in)
{
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 1 + tempGridsCellLevel - coverGridsCellLevel; k < fieldsGridsSize - tempGridsCellLevel + coverGridsCellLevel; k++)
                {           
                //check stopsign
                if( ptrArray_in[face][i][j][k]->StopSign() == 1) continue;

                double tempDensity;
                // set volume 
                double volume = ptrVolumeGridArray_in[i-1][j-1][k]; // face of ptrArray is greater than that of ptrVolumeGridArray
//                   std::cout << face << i << j << k << " " ;
//                   std::cout << " volume " << volume << " density " << ptrArray_in[face][i][j][k]->Density() << " ==> " ;
                ptrArray_in[face][i][j][k]->UpdateDueToWgt(ptrArray_in, volume, updateInfoPeriod_in);
                
                if( k < 1 + tempGridsCellLevel) 
                {
                    tempDensity =  ptrArray_in[face][i][j][k]->Density_H() + ptrArray_bot[face][i][j][k]->Density_H();
                    ptrArray_in[face][i][j][k]->Density_H( tempDensity);
                    tempDensity =  ptrArray_in[face][i][j][k]->Density_He() + ptrArray_bot[face][i][j][k]->Density_He();
                    ptrArray_in[face][i][j][k]->Density_He( tempDensity);
                    tempDensity =  ptrArray_in[face][i][j][k]->Density_O() + ptrArray_bot[face][i][j][k]->Density_O();
                    ptrArray_in[face][i][j][k]->Density_O( tempDensity);
                }
                if( k > fieldsGridsSize - tempGridsCellLevel - 1)
                {
                    int tempk = k - (fieldsGridsSize - tempGridsCellLevel);
                    tempDensity =  ptrArray_in[face][i][j][k]->Density_H() + ptrArray_top[face][i][j][tempk]->Density_H();
                    ptrArray_in[face][i][j][k]->Density_H( tempDensity);
                    tempDensity =  ptrArray_in[face][i][j][k]->Density_He() + ptrArray_top[face][i][j][tempk]->Density_He();
                    ptrArray_in[face][i][j][k]->Density_He( tempDensity);
                    tempDensity =  ptrArray_in[face][i][j][k]->Density_O() + ptrArray_top[face][i][j][tempk]->Density_O();
                    ptrArray_in[face][i][j][k]->Density_O( tempDensity);
                }
                // set stopSign
                ptrArray_in[face][i][j][k]->SetStopSign(1);
//              std::cout << ptrArray_in[face][i][j][k]->Density() << std::endl; 
                }
            }
        }
    }   
    // reset stopsign
    #pragma omp parallel for collapse(4)
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = 1; k < fieldsGridsSize; k++)
                {           
                // set stopSign
                ptrArray_in[face][i][j][k]->SetStopSign(0);
                }
            }
        }
    }      
}


//************************************************************************
//************************************************************************
// Create Cell centered field array for E for the type of Vector3
// The size of this array is [totalface * fsize+2 * fsize+2 * fsize]
Vector3***** EVectorCellArray( GridsPoints***** ptrArray)
{
    // Apply space to store
    static Vector3* mem_EVectorCellArray = new Vector3[totalFace * fieldsGridsSize * fieldsGridsSize * fieldsGridsSize];
    // define the pointer 
    Vector3 *****ptrEArray = new Vector3 ****[totalFace];
    for( int face = 0; face < totalFace; face++)
    {
        ptrEArray[face] = new Vector3***[fieldsGridsSize + 2];
        for( int i = 0; i < fieldsGridsSize + 2; i++)
        {
            ptrEArray[face][i] = new Vector3 **[fieldsGridsSize + 2];
            for( int j = 0; j < fieldsGridsSize + 2; j++)
            {
                ptrEArray[face][i][j] = new Vector3 *[fieldsGridsSize];
                for( int k = 0; k < fieldsGridsSize; k++)
                {
                    if( 1<=i && i<fieldsGridsSize+1 && 1<=j && j<fieldsGridsSize+1 )
                    {
                    ptrEArray[face][i][j][k] = mem_EVectorCellArray + face * fieldsGridsSize * fieldsGridsSize * fieldsGridsSize
                                                + (i-1) * fieldsGridsSize * fieldsGridsSize + (j-1) * fieldsGridsSize + k; 
                    } else
                    {
                        continue;
                    }
                    
                }
            }
        }
    }
    // covered area
    // face 0
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
            ptrEArray[0][i][0][k] = ptrEArray[5][i][fieldsGridsSize][k]; // bot

            ptrEArray[0][fieldsGridsSize+1][i][k] = ptrEArray[1][1][i][k]; // right

            ptrEArray[0][i][fieldsGridsSize+1][k] = ptrEArray[2][i][1][k]; // top

            ptrEArray[0][0][i][k] = ptrEArray[4][fieldsGridsSize][i][k];  // left
        }
    }
    // face 1
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrEArray[1][i][0][k] = ptrEArray[5][fieldsGridsSize][fieldsGridsSize+1-i][k]; // bot
        
        ptrEArray[1][fieldsGridsSize+1][i][k] = ptrEArray[3][1][i][k]; // right

        ptrEArray[1][i][fieldsGridsSize+1][k] = ptrEArray[2][fieldsGridsSize][i][k]; // top

        ptrEArray[1][0][i][k] = ptrEArray[0][fieldsGridsSize][i][k];  // left
        }
    }
    // face 2
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrEArray[2][i][0][k] = ptrEArray[0][i][fieldsGridsSize][k]; // bot
        
        ptrEArray[2][fieldsGridsSize+1][i][k] = ptrEArray[1][i][fieldsGridsSize][k]; // right
        
        ptrEArray[2][i][fieldsGridsSize+1][k] = ptrEArray[3][fieldsGridsSize+1-i][fieldsGridsSize][k]; // top
        
        ptrEArray[2][0][i][k] = ptrEArray[4][fieldsGridsSize+1-i][fieldsGridsSize][k];  // left
        }
    }
    //face 3
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrEArray[3][i][0][k] = ptrEArray[5][fieldsGridsSize+1-i][1][k]; // bot

        ptrEArray[3][fieldsGridsSize+1][i][k] = ptrEArray[4][1][i][k]; // right

        ptrEArray[3][i][fieldsGridsSize+1][k] = ptrEArray[2][fieldsGridsSize+1-i][fieldsGridsSize][k]; // top
        
        ptrEArray[3][0][i][k] = ptrEArray[1][fieldsGridsSize][i][k];  // left
        }
    }
    // face 4
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrEArray[4][i][0][k] = ptrEArray[5][1][i][k]; // bot
        
        ptrEArray[4][fieldsGridsSize+1][i][k] = ptrEArray[0][1][i][k]; // right
        
        ptrEArray[4][i][fieldsGridsSize+1][k] = ptrEArray[2][1][fieldsGridsSize+1-i][k]; // top
        
        ptrEArray[4][0][i][k] = ptrEArray[3][fieldsGridsSize][i][k];  // left
        }
    }
    // face 5
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrEArray[5][i][0][k] = ptrEArray[3][fieldsGridsSize+1-i][1][k]; // bot
        
        ptrEArray[5][fieldsGridsSize+1][i][k] = ptrEArray[1][fieldsGridsSize+1-i][1][k]; // right
        
        ptrEArray[5][i][fieldsGridsSize+1][k] = ptrEArray[0][i][1][k]; // top
        
        ptrEArray[5][0][i][k] = ptrEArray[4][i][1][k];  // left    
        }
    }

    return ptrEArray;
}


//************************************************************************
//************************************************************************
// Prerun 1.6 // Create const array of B at center of each cells
// [totalface * fsize+2 * fsize+2 * fsize +2]
// Most code are the same with that of EVectorCellArray
Vector3***** BVectorCellArray( GridsPoints***** ptrArray)
{
    // Apply space to store
    static Vector3* mem_BVectorCellArray = new Vector3[totalFace * fieldsGridsSize * fieldsGridsSize * fieldsGridsSize];
    // define the pointer 
    Vector3 *****ptrBArray = new Vector3 ****[totalFace];
    for( int face = 0; face < totalFace; face++)
    {
        ptrBArray[face] = new Vector3***[fieldsGridsSize + 2];
        for( int i = 0; i < fieldsGridsSize + 2; i++)
        {
            ptrBArray[face][i] = new Vector3 **[fieldsGridsSize + 2];
            for( int j = 0; j < fieldsGridsSize + 2; j++)
            {
                ptrBArray[face][i][j] = new Vector3 *[fieldsGridsSize];
                for( int k = 0; k < fieldsGridsSize; k++)
                {
                    if( 1<=i && i<fieldsGridsSize+1 && 1<=j && j<fieldsGridsSize+1 )
                    {
                    ptrBArray[face][i][j][k] = mem_BVectorCellArray + face * fieldsGridsSize * fieldsGridsSize * fieldsGridsSize
                                                + (i-1) * fieldsGridsSize * fieldsGridsSize + (j-1) * fieldsGridsSize + k; 
                    } else
                    {
                        continue;
                    }
                    
                }
            }
        }
    }
    // covered area
    // face 0
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
            ptrBArray[0][i][0][k] = ptrBArray[5][i][fieldsGridsSize][k]; // bot

            ptrBArray[0][fieldsGridsSize+1][i][k] = ptrBArray[1][1][i][k]; // right

            ptrBArray[0][i][fieldsGridsSize+1][k] = ptrBArray[2][i][1][k]; // top

            ptrBArray[0][0][i][k] = ptrBArray[4][fieldsGridsSize][i][k];  // left
        }
    }
    // face 1
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrBArray[1][i][0][k] = ptrBArray[5][fieldsGridsSize][fieldsGridsSize+1-i][k]; // bot
        
        ptrBArray[1][fieldsGridsSize+1][i][k] = ptrBArray[3][1][i][k]; // right

        ptrBArray[1][i][fieldsGridsSize+1][k] = ptrBArray[2][fieldsGridsSize][i][k]; // top

        ptrBArray[1][0][i][k] = ptrBArray[0][fieldsGridsSize][i][k];  // left
        }
    }
    // face 2
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrBArray[2][i][0][k] = ptrBArray[0][i][fieldsGridsSize][k]; // bot
        
        ptrBArray[2][fieldsGridsSize+1][i][k] = ptrBArray[1][i][fieldsGridsSize][k]; // right
        
        ptrBArray[2][i][fieldsGridsSize+1][k] = ptrBArray[3][fieldsGridsSize+1-i][fieldsGridsSize][k]; // top
        
        ptrBArray[2][0][i][k] = ptrBArray[4][fieldsGridsSize+1-i][fieldsGridsSize][k];  // left
        }
    }
    //face 3
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrBArray[3][i][0][k] = ptrBArray[5][fieldsGridsSize+1-i][1][k]; // bot

        ptrBArray[3][fieldsGridsSize+1][i][k] = ptrBArray[4][1][i][k]; // right

        ptrBArray[3][i][fieldsGridsSize+1][k] = ptrBArray[2][fieldsGridsSize+1-i][fieldsGridsSize][k]; // top
        
        ptrBArray[3][0][i][k] = ptrBArray[1][fieldsGridsSize][i][k];  // left
        }
    }
    // face 4
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrBArray[4][i][0][k] = ptrBArray[5][1][i][k]; // bot
        
        ptrBArray[4][fieldsGridsSize+1][i][k] = ptrBArray[0][1][i][k]; // right
        
        ptrBArray[4][i][fieldsGridsSize+1][k] = ptrBArray[2][1][fieldsGridsSize+1-i][k]; // top
        
        ptrBArray[4][0][i][k] = ptrBArray[3][fieldsGridsSize][i][k];  // left
        }
    }
    // face 5
    for( int i = 1; i < fieldsGridsSize+1; i++)
    {
        for( int k = 0; k < fieldsGridsSize; k++)
        {
        ptrBArray[5][i][0][k] = ptrBArray[3][fieldsGridsSize+1-i][1][k]; // bot
        
        ptrBArray[5][fieldsGridsSize+1][i][k] = ptrBArray[1][fieldsGridsSize+1-i][1][k]; // right
        
        ptrBArray[5][i][fieldsGridsSize+1][k] = ptrBArray[0][i][1][k]; // top
        
        ptrBArray[5][0][i][k] = ptrBArray[4][i][1][k];  // left    
        }
    }

    Vector3 tempB;
    for( int face = 0; face < totalFace; face++)
    {
        for( int i = 0; i < fieldsGridsSize; i++)
        {
            for( int j = 0; j < fieldsGridsSize; j++)
            {
                for( int k = 0; k < fieldsGridsSize; k++)
                {
                    //Set the Vector at the center of cells

                }
            }
        }
    }

    return ptrBArray;

}




//************************************************************************
//************************************************************************
// FUNCTION 
// Set up a vector array to store the B on face

// The size of this array is [direction * face * (fsize+1) * (fsize+1) * (fsize+1)]
// The size of this array is [direction * face * (fsize+2) * (fsize+2) * (fsize+1)] X


Vector3***** BVectorFaceArray( GridsPoints***** ptrArray_in)
{
    static Vector3* mem_BVectorFaceArray = new Vector3[ 3 * totalFace * (fieldsGridsSize+1) * (fieldsGridsSize+1) *(fieldsGridsSize+1)];
    Vector3***** ptrBFaceArray = new Vector3 ****[3];
    for( int direction = 0; direction < 3; direction++)
    {
        ptrBFaceArray[direction] = new Vector3***[totalFace];
        for( int face = 0; face < totalFace; face++)
        {
            ptrBFaceArray[direction][face] = new Vector3**[fieldsGridsSize+1];
            for( int i = 0; i < fieldsGridsSize+1; i++)
            {
                ptrBFaceArray[direction][face][i] = new Vector3*[fieldsGridsSize+1];
                for( int j = 0; j<fieldsGridsSize+1; j++)
                {
//                    ptrBFaceArray[direction][face][i][j] = new Vector3[fieldsGridsSize+1];
                    ptrBFaceArray[direction][face][i][j] = mem_BVectorFaceArray + direction * totalFace * (fieldsGridsSize+1) * (fieldsGridsSize+1)* (fieldsGridsSize+1)
                                                        + face * (fieldsGridsSize+1)* (fieldsGridsSize+1)* (fieldsGridsSize+1)
                                                        + i * (fieldsGridsSize+1)* (fieldsGridsSize+1)
                                                        + j * (fieldsGridsSize+1);
                    for( int k = 0; k<fieldsGridsSize+1; k++)
                    {
                        int I = i+1;
                        int J = j+1;
                        int K = k;
                        Vector3 tempB, tempPos;
                        if( direction == 0) // face perpendicular to i direction 
                        {
                            if( k == fieldsGridsSize || j == fieldsGridsSize) continue;
                            tempPos = ptrArray_in[face][I][J][K]->Pos3().PlusProduct( ptrArray_in[face][I][J+1][K]->Pos3());
                            tempPos = tempPos.PlusProduct( ptrArray_in[face][I][J][K+1]->Pos3()).PlusProduct( ptrArray_in[face][I][J+1][K+1]->Pos3());
                            tempPos = tempPos.ScaleProduct(0.25);
                        } else if ( direction ==1)  // face perpendicular to j direction
                        {
                            if( k == fieldsGridsSize || i == fieldsGridsSize) continue;
                            tempPos = ptrArray_in[face][I][J][K]->Pos3().PlusProduct( ptrArray_in[face][I+1][J][K]->Pos3());
                            tempPos = tempPos.PlusProduct( ptrArray_in[face][I][J][K+1]->Pos3()).PlusProduct( ptrArray_in[face][I+1][J][K+1]->Pos3());
                            tempPos = tempPos.ScaleProduct(0.25);
                        } else if ( direction ==2)  // face perpendicular to k direction
                        {
                            if( i == fieldsGridsSize || j == fieldsGridsSize) continue;
                            tempPos = ptrArray_in[face][I][J][K]->Pos3().PlusProduct( ptrArray_in[face][I+1][J][K]->Pos3());
                            tempPos = tempPos.PlusProduct( ptrArray_in[face][I][J+1][K]->Pos3()).PlusProduct( ptrArray_in[face][I+1][J+1][K]->Pos3());
                            tempPos = tempPos.ScaleProduct(0.25);
                        }

                        double r = sqrt(pow(tempPos.x(),2.0) + pow(tempPos.y(),2.0) + pow(tempPos.z(),2.0));
                        tempB.Setx( 3 * dMoment * tempPos.x() * tempPos.z() / pow(r,5.0));
                        tempB.Sety( 3 * dMoment * tempPos.y() * tempPos.z() / pow(r,5.0));
                        tempB.Setz( dMoment * (3 * pow(tempPos.z(),2.0) - pow(r,2.0)) / pow(r,5.0));
                    //    ptrBFaceArray[direction][face][i][j][k] = tempB;
                    // dB initialization
                        ptrBFaceArray[direction][face][i][j][k] = { 0.0, 0.0, 0.0};

                    }
                }
            }
        }
    }
    
    return ptrBFaceArray;
}


//************************************************************************
//************************************************************************
// FUNCTION 
// Update the B on each face from BVectorFaceArray
// Calculate dB/dt over adjacent faces (madsen1995)
void BVectorFaceArrayUpdate( GridsPoints***** ptrArray_in, Vector3***** ptrBFaceArray_in)
{   
    // i direction
    // face i j k 
    // adjacent grid points:ptaArray[face][i+1][j+1][k]
    //                      ptaArray[face][i+1][j+2][k]
    //                      ptaArray[face][i+1][j+1][k+1]
    //                      ptaArray[face][i+1][j+2][k+1]
    // adjacent grid points outside:ptaArray[face][i][j+1][k]
    //                              ptaArray[face][i][j+2][k]
    //                              ptaArray[face][i][j+1][k+1]
    //                              ptaArray[face][i][j+2][k+1]
    // adjacent grid points inside: ptaArray[face][i+2][j+1][k]
    //                              ptaArray[face][i+2][j+2][k]
    //                              ptaArray[face][i+2][j+1][k+1]
    //                              ptaArray[face][i+2][j+2][k+1]
    // 20 length with E must be indentified
    // 
    //  Using gridspoints E to average length E to simplify the calculation
    // matrix for calculating the face B need:
    // 3 face vector, 3 circle intergration with length E
    //
    
    // index are for the [fieldgridsize+2][fieldgridsize+2][fieldgridsize+2]
    Vector3 dBOnFace, sumtempB;
    Vector3 AFace, BFace, CFace;
    double weightB, sumWeightB;
    double AInteger, BInteger, CInteger;

    for( int direction = 0; direction < 3; direction++)
    {
        for( int face = 0; face < totalFace; face ++)
        {
            // index of cell No., total range is from 0 - fsize+1, 
            for( int i = 1; i < fieldsGridsSize +2; i++)
            {
                for( int j = 1; j < fieldsGridsSize+2; j++)
                {
                    for( int k = tempGridsCellLevel; k < fieldsGridsSize-tempGridsCellLevel+1; k++)
                    {
                        if( direction == 0) // perpendicular to i direction
                        {
                            if( j == fieldsGridsSize+1 || k == fieldsGridsSize-tempGridsCellLevel)
                            continue;
                           //face vector 
                            AFace = AreaVectorT( ptrArray_in, face, i-1, j, k);
                            BFace = AreaVectorF( ptrArray_in, face, i-1, j, k);
                            CFace = AreaVectorR( ptrArray_in, face, i-1, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationT( ptrArray_in, face, i-1, j, k);
                            BInteger = EIntegrationF( ptrArray_in, face, i-1, j, k);
                            CInteger = EIntegrationR( ptrArray_in, face, i-1, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB = dBOnFace.ScaleProduct(weightB);
                            sumWeightB = weightB;
                            
                            AFace = AreaVectorF( ptrArray_in, face, i-1, j, k);
                            BFace = AreaVectorBot( ptrArray_in, face, i-1, j, k);
                            CFace = AreaVectorR( ptrArray_in, face, i-1, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationF( ptrArray_in, face, i-1, j, k);
                            BInteger = EIntegrationBot( ptrArray_in, face, i-1, j, k);
                            CInteger = EIntegrationR( ptrArray_in, face, i-1, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorBot( ptrArray_in, face, i-1, j, k);
                            BFace = AreaVectorBack( ptrArray_in, face, i-1, j, k);
                            CFace = AreaVectorR( ptrArray_in, face, i-1, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBot( ptrArray_in, face, i-1, j, k);
                            BInteger = EIntegrationBack( ptrArray_in, face, i-1, j, k);
                            CInteger = EIntegrationR( ptrArray_in, face, i-1, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            AFace = AreaVectorBack( ptrArray_in, face, i-1, j, k);
                            BFace = AreaVectorT( ptrArray_in, face, i-1, j, k);
                            CFace = AreaVectorR( ptrArray_in, face, i-1, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBack( ptrArray_in, face, i-1, j, k);
                            BInteger = EIntegrationT( ptrArray_in, face, i-1, j, k);
                            CInteger = EIntegrationR( ptrArray_in, face, i-1, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            AFace = AreaVectorT( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationT( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            AFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorF( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationF( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorF( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorT( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationF( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationT( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            dBOnFace = sumtempB.ScaleProduct( 1.0 / sumWeightB);
                            ptrBFaceArray_in[direction][face][i-1][j-1][k] = 
                            ptrBFaceArray_in[direction][face][i-1][j-1][k].PlusProduct(dBOnFace.ScaleProduct(tstep));

                        } else if( direction == 1) // perpendicular to j direction
                        {
                            if( i == fieldsGridsSize+1 || k == fieldsGridsSize-tempGridsCellLevel)
                            continue;
                            AFace = AreaVectorR( ptrArray_in, face, i, j-1, k);
                            BFace = AreaVectorBack( ptrArray_in, face, i, j-1, k);
                            CFace = AreaVectorT( ptrArray_in, face, i, j-1, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationR( ptrArray_in, face, i, j-1, k);
                            BInteger = EIntegrationBack( ptrArray_in, face, i, j-1, k);
                            CInteger = EIntegrationT( ptrArray_in, face, i, j-1, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB = dBOnFace.ScaleProduct(weightB);
                            sumWeightB = weightB;
                            
                            AFace = AreaVectorBack( ptrArray_in, face, i, j-1, k);
                            BFace = AreaVectorL( ptrArray_in, face, i, j-1, k);
                            CFace = AreaVectorT( ptrArray_in, face, i, j-1, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBack( ptrArray_in, face, i, j-1, k);
                            BInteger = EIntegrationL( ptrArray_in, face, i, j-1, k);
                            CInteger = EIntegrationT( ptrArray_in, face, i, j-1, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorL( ptrArray_in, face, i, j-1, k);
                            BFace = AreaVectorF( ptrArray_in, face, i, j-1, k);
                            CFace = AreaVectorT( ptrArray_in, face, i, j-1, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationL( ptrArray_in, face, i, j-1, k);
                            BInteger = EIntegrationF( ptrArray_in, face, i, j-1, k);
                            CInteger = EIntegrationT( ptrArray_in, face, i, j-1, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorF( ptrArray_in, face, i, j-1, k);
                            BFace = AreaVectorR( ptrArray_in, face, i, j-1, k);
                            CFace = AreaVectorT( ptrArray_in, face, i, j-1, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationF( ptrArray_in, face, i, j-1, k);
                            BInteger = EIntegrationR( ptrArray_in, face, i, j-1, k);
                            CInteger = EIntegrationT( ptrArray_in, face, i, j-1, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorR( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorF( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationR( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationF( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            AFace = AreaVectorF( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationF( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            AFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorR( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationR( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;

                            dBOnFace = sumtempB.ScaleProduct( 1.0 / sumWeightB);
                            ptrBFaceArray_in[direction][face][i-1][j-1][k] = 
                            ptrBFaceArray_in[direction][face][i-1][j-1][k].PlusProduct(dBOnFace.ScaleProduct(tstep));
                        } else
                        {
                            if( i == fieldsGridsSize+1 || j == fieldsGridsSize+1)
                            continue;
                            AFace = AreaVectorT( ptrArray_in, face, i, j, k-1);
                            BFace = AreaVectorL( ptrArray_in, face, i, j, k-1);
                            CFace = AreaVectorF( ptrArray_in, face, i, j, k-1);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationT( ptrArray_in, face, i, j, k-1);
                            BInteger = EIntegrationL( ptrArray_in, face, i, j, k-1);
                            CInteger = EIntegrationF( ptrArray_in, face, i, j, k-1);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB = dBOnFace.ScaleProduct(weightB);
                            sumWeightB = weightB;
                            
                            AFace = AreaVectorL( ptrArray_in, face, i, j, k-1);
                            BFace = AreaVectorBot( ptrArray_in, face, i, j, k-1);
                            CFace = AreaVectorF( ptrArray_in, face, i, j, k-1);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationL( ptrArray_in, face, i, j, k-1);
                            BInteger = EIntegrationBot( ptrArray_in, face, i, j, k-1);
                            CInteger = EIntegrationF( ptrArray_in, face, i, j, k-1);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorBot( ptrArray_in, face, i, j, k-1);
                            BFace = AreaVectorR( ptrArray_in, face, i, j, k-1);
                            CFace = AreaVectorF( ptrArray_in, face, i, j, k-1);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBot( ptrArray_in, face, i, j, k-1);
                            BInteger = EIntegrationR( ptrArray_in, face, i, j, k-1);
                            CInteger = EIntegrationF( ptrArray_in, face, i, j, k-1);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorR( ptrArray_in, face, i, j, k-1);
                            BFace = AreaVectorT( ptrArray_in, face, i, j, k-1);
                            CFace = AreaVectorF( ptrArray_in, face, i, j, k-1);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationR( ptrArray_in, face, i, j, k-1);
                            BInteger = EIntegrationT( ptrArray_in, face, i, j, k-1);
                            CInteger = EIntegrationF( ptrArray_in, face, i, j, k-1);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorT( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorR( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationT( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationR( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorR( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationR( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorBot( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationBot( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            AFace = AreaVectorL( ptrArray_in, face, i, j, k);
                            BFace = AreaVectorT( ptrArray_in, face, i, j, k);
                            CFace = AreaVectorBack( ptrArray_in, face, i, j, k);
                            weightB = AFace.CrossProduct(BFace).DotProduct(CFace);
                            AInteger = EIntegrationL( ptrArray_in, face, i, j, k);
                            BInteger = EIntegrationT( ptrArray_in, face, i, j, k);
                            CInteger = EIntegrationBack( ptrArray_in, face, i, j, k);
                            dBOnFace.FaceBSolver( AFace, BFace, CFace, AInteger, BInteger, CInteger); 
                            sumtempB.PlusProduct( dBOnFace.ScaleProduct(weightB));
                            sumWeightB += weightB;
                            
                            dBOnFace = sumtempB.ScaleProduct( 1.0 / sumWeightB);
                            ptrBFaceArray_in[direction][face][i-1][j-1][k] = 
                            ptrBFaceArray_in[direction][face][i-1][j-1][k].PlusProduct(dBOnFace.ScaleProduct(tstep));
                        }
                    }
                }
            }
        }
    }   
}

// ***************************************************************************************
// Calculate curl B at the center of cells

Vector3*** CurlBCellArray( GridsPoints***** ptrArray_in, 
                           Vector3*** ptrVectorCellArray, 
                           Vector3***** ptrBVectorFaceArray, 
                           double*** ptrVolumeCellArray,
                           int face_in)
{
    int i, j, k;
    // I, J, K is the cell index
    for( int I = 1; I < fieldsGridsSize+1; I++)
    {
        for( int J = 1; J < fieldsGridsSize+1; J++)
        {
            for( int K = tempGridsCellLevel; K < fieldsGridsSize - tempGridsCellLevel; K++)
            {
                i = I-1;
                j = J-1;
                k = K;
                
                Vector3 temp = AreaVectorL( ptrArray_in, face_in, I, J, K).CrossProduct(
                               ptrBVectorFaceArray[0][face_in][i][j][k]);
                        temp = temp.PlusProduct(
                               AreaVectorR( ptrArray_in, face_in, I, J, K).CrossProduct(
                               ptrBVectorFaceArray[0][face_in][i+1][j][k]));
                
                        temp = temp.PlusProduct(
                               AreaVectorT( ptrArray_in, face_in, I, J, K).CrossProduct(
                               ptrBVectorFaceArray[1][face_in][i][j+1][k]));
                        temp = temp.PlusProduct(
                               AreaVectorBot( ptrArray_in, face_in, I, J, K).CrossProduct(
                               ptrBVectorFaceArray[1][face_in][i][j][k]));
                        temp = temp.PlusProduct(
                               AreaVectorF( ptrArray_in, face_in, I, J, K).CrossProduct(
                               ptrBVectorFaceArray[2][face_in][i][j][k+1]));
                        temp = temp.PlusProduct(
                               AreaVectorBack( ptrArray_in, face_in, I, J, K).CrossProduct(
                               ptrBVectorFaceArray[2][face_in][i][j][k]));
                double volumetemp = ptrVolumeCellArray[i][j][k];

                temp = temp.ScaleProduct( 1.0 / volumetemp);
                ptrVectorCellArray[i][j][k].SetVector3( temp); 
            }
        }
    }
    return ptrVectorCellArray;
}

// *********************************************************************
// Update E at the centers of cells
// with the (curl B), (ve), (grad Pe) at the centers of cells
// Notice the size of ptrEVectorCellArray is [6][fsize+2][fsize+2][fsize]
void UpdateECellArray(  GridsPoints***** ptrArray, 
                        Vector3***** ptrEVectorCellArray,
                        Vector3*** ptrVeleVectorCellArray,
                        Vector3*** curlBCellArray,
                        Vector3*** ptrGradVectorCellArray,
                        int face)
{   
    Vector3 Vele, Veli;
    double density;
    Vector3 tempP, tempB;
    

    for( int i = 1; i < fieldsGridsSize+3; i++)
    {
        for( int j = 1; j < fieldsGridsSize+3; j++)
        {
            for( int k = tempGridsCellLevel+1; k < fieldsGridsSize - tempGridsCellLevel+1; k++)
            {
                if((i==1&&j==1)||(i==1&&j==fieldsGridsSize+2)||
                (i==fieldsGridsSize+2&&j==1)||(i==fieldsGridsSize+2&&j==fieldsGridsSize+2))
                {
                    continue;
                }else 
                {
                Veli = ptrArray[face][i-1][j-1][k-1]->Vel3().PlusProduct(
                                    ptrArray[face][i][j-1][k-1]->Vel3() );
                Veli = Veli.PlusProduct(           
                                    ptrArray[face][i-1][j][k-1]->Vel3());
                Veli = Veli.PlusProduct(
                                    ptrArray[face][i][j][k-1]->Vel3());
                Veli = Veli.PlusProduct(
                                    ptrArray[face][i-1][j-1][k]->Vel3());
                Veli = Veli.PlusProduct(
                                    ptrArray[face][i][j-1][k]->Vel3());
                Veli = Veli.PlusProduct(
                                    ptrArray[face][i-1][j][k]->Vel3());    
                Veli = Veli.PlusProduct(
                                    ptrArray[face][i][j][k]->Vel3()).ScaleProduct(1.0/8.0);
            
                density =(ptrArray[face][i-1][j-1][k-1]->Density() +
                          ptrArray[face][i][j-1][k-1]->Density() +
                          ptrArray[face][i-1][j][k-1]->Density() +
                          ptrArray[face][i][j][k-1]->Density() +
                          ptrArray[face][i-1][j-1][k]->Density() +
                          ptrArray[face][i][j-1][k]->Density() +
                          ptrArray[face][i-1][j][k]->Density() +
                          ptrArray[face][i][j][k]->Density()) / 8.0;

                tempB =Vector3(ptrArray[face][i-1][j-1][k-1]->B3().x() +
                               ptrArray[face][i][j-1][k-1]->B3().x() +
                               ptrArray[face][i-1][j][k-1]->B3().x() +
                               ptrArray[face][i][j][k-1]->B3().x() +
                               ptrArray[face][i-1][j-1][k]->B3().x() +
                               ptrArray[face][i][j-1][k]->B3().x() +
                               ptrArray[face][i-1][j][k]->B3().x() +
                               ptrArray[face][i][j][k]->B3().x(),
                               ptrArray[face][i-1][j-1][k-1]->B3().y() +
                               ptrArray[face][i][j-1][k-1]->B3().y() +
                               ptrArray[face][i-1][j][k-1]->B3().y() +
                               ptrArray[face][i][j][k-1]->B3().y() +
                               ptrArray[face][i-1][j-1][k]->B3().y() +
                               ptrArray[face][i][j-1][k]->B3().y() +
                               ptrArray[face][i-1][j][k]->B3().y() +
                               ptrArray[face][i][j][k]->B3().y(),
                               ptrArray[face][i-1][j-1][k-1]->B3().z() +
                               ptrArray[face][i][j-1][k-1]->B3().z() +
                               ptrArray[face][i-1][j][k-1]->B3().z() +
                               ptrArray[face][i][j][k-1]->B3().z() +
                               ptrArray[face][i-1][j-1][k]->B3().z() +
                               ptrArray[face][i][j-1][k]->B3().z() +
                               ptrArray[face][i-1][j][k]->B3().z() +
                               ptrArray[face][i][j][k]->B3().z());
                tempB = tempB.ScaleProduct(1.0 / 8.0);
                if( density!=0)
                {
                Vele =  Veli.MinusProduct(curlBCellArray[i-1][j-1][k-1].ScaleProduct(1.0 / (mu0 * qi0 * density)));
                
                tempP = ptrGradVectorCellArray[i-1][j-1][k-1].ScaleProduct(1.0 / qi0 / density);
                }else
                {
                    Vele = Vector3{0.0,0.0,0.0};
                    tempP = Vector3{0.0,0.0,0.0};
                }
                
                ptrVeleVectorCellArray[i-1][j-1][k-1].SetVector3( Vele);


                ptrEVectorCellArray[face][i-1][j-1][k-1]->SetVector3( tempB.CrossProduct(Vele).PlusProduct(tempP).ScaleProduct(-1.0));
                }
            }
        }
    }
    
    

    for( int i = 1; i < fieldsGridsSize+2; i++)
    {
        for( int j = 1; j < fieldsGridsSize+2; j++)
        {
            for( int k = tempGridsCellLevel+1; k < fieldsGridsSize - tempGridsCellLevel; k++)
            {
                Vector3 EVector = Vector3(0.0, 0.0, 0.0);
                Vector3 VeleVector = Vector3( 0.0, 0.0, 0.0);
                if(i==1&&j==1) 
                {
                EVector = ptrEVectorCellArray[face][1][0][k-1]->PlusProduct(
                                    ptrEVectorCellArray[face][1][1][k-1]->V3());
                EVector = EVector.PlusProduct(           
                                    ptrEVectorCellArray[face][0][1][k-1]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][1][0][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][1][1][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][0][1][k]->V3()).ScaleProduct(1.0/6.0);   

                                    
                VeleVector = ptrVeleVectorCellArray[1][0][k-1].PlusProduct(
                                    ptrVeleVectorCellArray[1][1][k-1].V3());
                VeleVector = VeleVector.PlusProduct(           
                                    ptrVeleVectorCellArray[0][1][k-1].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[1][0][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[1][1][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[0][1][k].V3()).ScaleProduct(1.0/6.0);            
                }
                else if(i==1&&j==fieldsGridsSize+1) 
                {
                
                EVector = ptrEVectorCellArray[face][1][fieldsGridsSize+1][k-1]->PlusProduct(
                                    ptrEVectorCellArray[face][1][fieldsGridsSize][k-1]->V3());
                EVector = EVector.PlusProduct(           
                                    ptrEVectorCellArray[face][0][fieldsGridsSize][k-1]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][1][fieldsGridsSize+1][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][1][fieldsGridsSize][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][0][fieldsGridsSize][k]->V3()).ScaleProduct(1.0/6.0);

                                    
                VeleVector = ptrVeleVectorCellArray[1][fieldsGridsSize+1][k-1].PlusProduct(
                                    ptrVeleVectorCellArray[1][fieldsGridsSize][k-1].V3());
                VeleVector = VeleVector.PlusProduct(           
                                    ptrVeleVectorCellArray[0][fieldsGridsSize][k-1].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[1][fieldsGridsSize+1][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[1][fieldsGridsSize][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[0][fieldsGridsSize][k].V3()).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==fieldsGridsSize+1)
                {
                EVector = ptrEVectorCellArray[face][fieldsGridsSize][fieldsGridsSize+1][k-1]->PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize][fieldsGridsSize][k-1]->V3());
                EVector = EVector.PlusProduct(           
                                    ptrEVectorCellArray[face][fieldsGridsSize+1][fieldsGridsSize][k-1]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize][fieldsGridsSize+1][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize][fieldsGridsSize][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize+1][fieldsGridsSize][k]->V3()).ScaleProduct(1.0/6.0);
                                    
                VeleVector = ptrVeleVectorCellArray[fieldsGridsSize][fieldsGridsSize+1][k-1].PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize][fieldsGridsSize][k-1].V3());
                VeleVector = VeleVector.PlusProduct(           
                                    ptrVeleVectorCellArray[fieldsGridsSize+1][fieldsGridsSize][k-1].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize][fieldsGridsSize+1][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize][fieldsGridsSize][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize+1][fieldsGridsSize][k].V3()).ScaleProduct(1.0/6.0);
                }
                else if(i==fieldsGridsSize+1&&j==1) 
                {
                EVector = ptrEVectorCellArray[face][fieldsGridsSize][0][k-1]->PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize][1][k-1]->V3());
                EVector = EVector.PlusProduct(           
                                    ptrEVectorCellArray[face][fieldsGridsSize+1][1][k-1]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize][0][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize][1][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][fieldsGridsSize+1][1][k]->V3()).ScaleProduct(1.0/6.0);      
                                    
                VeleVector = ptrVeleVectorCellArray[fieldsGridsSize][0][k-1].PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize][1][k-1].V3());
                VeleVector = VeleVector.PlusProduct(           
                                    ptrVeleVectorCellArray[fieldsGridsSize+1][1][k-1].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize][0][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize][1][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[fieldsGridsSize+1][1][k].V3()).ScaleProduct(1.0/6.0);           
                } else
                {
                EVector = ptrEVectorCellArray[face][i-1][j-1][k-1]->PlusProduct(
                                    ptrEVectorCellArray[face][i][j-1][k-1]->V3());
                EVector = EVector.PlusProduct(           
                                    ptrEVectorCellArray[face][i-1][j][k-1]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][i][j][k-1]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][i-1][j-1][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][i][j-1][k]->V3());
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][i-1][j][k]->V3());    
                EVector = EVector.PlusProduct(
                                    ptrEVectorCellArray[face][i][j][k]->V3()).ScaleProduct(1.0/8.0);
                                    
                VeleVector = ptrVeleVectorCellArray[i-1][j-1][k-1].PlusProduct(
                                    ptrVeleVectorCellArray[i][j-1][k-1].V3());
                VeleVector = VeleVector.PlusProduct(           
                                    ptrVeleVectorCellArray[i-1][j][k-1].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[i][j][k-1].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[i-1][j-1][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[i][j-1][k].V3());
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[i-1][j][k].V3());    
                VeleVector = VeleVector.PlusProduct(
                                    ptrVeleVectorCellArray[i][j][k].V3()).ScaleProduct(1.0/8.0);
                }
                // update E
        
                ptrArray[face][i][j][k]->SetE3( EVector);
                ptrArray[face][i][j][k]->SetVel_e3( VeleVector);
        //    std::cout << " VeleVector"<< VeleVector.x() << " " << VeleVector.y() << " " << VeleVector.z() << std::endl;
            
            //    std::cout << i << " " << j << " " << k << " " << ptrVeleVectorCellArray[i][j][k].x() << " " <<ptrVeleVectorCellArray[i][j][k].y() << " " << ptrVeleVectorCellArray[i][j][k].z() << std::endl;
        //        std::cout << ptrArray[face][i][j][k]->Vel_e3().x() << " " << ptrArray[face][i][j][k]->Vel_e3().y() << " " << ptrArray[face][i][j][k]->Vel_e3().z() << std::endl;
        //        std::cout << " EVector"<< EVector.x() << " " << EVector.y() << " " << EVector.z() << std::endl;
        //        std::cout << ptrArray[face][i][j][k]->E3().x() << " " <<ptrArray[face][i][j][k]->E3().y() << " " <<ptrArray[face][i][j][k]->E3().z() << std::endl << std::endl;
            }
        }
    }        
    
}

// ******************************************************
// Update the B on each grids
// 
void BVectorGridsArrayUpdate(   GridsPoints***** ptrArray, 
                                Vector3***** ptrBVectorFaceArray)
{
    Vector3 Btemp = Vector3(0.0, 0.0, 0.0);
    for( int face = 0; face < totalFace; face++)
    {
        // cell index, the total range is from 0 - fsize+1
        for( int i = 1; i < fieldsGridsSize+2; i++)
        {
            for( int j = 1; j < fieldsGridsSize+2; j++)
            {
                for( int k = tempGridsCellLevel; k < fieldsGridsSize - tempGridsCellLevel+1; k++)
                {
                    if( i == 1 && j == 1 ||
                        i == 1 && j == fieldsGridsSize+1 ||
                        i == fieldsGridsSize+1 && j ==1 ||
                        i == fieldsGridsSize+1 && j == fieldsGridsSize+1)
                        continue;

                    if( i == 1  || i == fieldsGridsSize+1)
                    {
                        Btemp = ptrBVectorFaceArray[0][face][i-1][j-2][k-1].PlusProduct(
                            ptrBVectorFaceArray[0][face][i-1][j-2][k-1]).PlusProduct(
                            ptrBVectorFaceArray[0][face][i-1][j-1][k]).PlusProduct(
                            ptrBVectorFaceArray[0][face][i-1][j-1][k]).ScaleProduct( 1.0 / 4.0);     
                        ptrArray[face][i][j][k]->SetdB3(Btemp);
                        continue;
                    }
           
                    if( j == 1  || j == fieldsGridsSize+1)
                    {
                        Btemp = ptrBVectorFaceArray[1][face][i-2][j-1][k-1].PlusProduct(
                            ptrBVectorFaceArray[1][face][i-2][j-1][k-1]).PlusProduct(
                            ptrBVectorFaceArray[1][face][i-1][j-1][k]).PlusProduct(
                            ptrBVectorFaceArray[1][face][i-1][j-1][k]).ScaleProduct( 1.0 / 4.0) ;
                        ptrArray[face][i][j][k]->SetdB3(Btemp);
                        continue;
                    }
                    Btemp = ptrBVectorFaceArray[0][face][i-1][j-2][k-1].PlusProduct(
                            ptrBVectorFaceArray[0][face][i-1][j-2][k-1]).PlusProduct(
                            ptrBVectorFaceArray[0][face][i-1][j-1][k]).PlusProduct(
                            ptrBVectorFaceArray[0][face][i-1][j-1][k]).PlusProduct(
                            ptrBVectorFaceArray[1][face][i-2][j-1][k-1]).PlusProduct(
                            ptrBVectorFaceArray[1][face][i-2][j-1][k-1]).PlusProduct(
                            ptrBVectorFaceArray[1][face][i-1][j-1][k]).PlusProduct(
                            ptrBVectorFaceArray[1][face][i-1][j-1][k]).ScaleProduct( 1.0 / 8.0);
                    ptrArray[face][i][j][k]->SetdB3(Btemp);
                }
            }
        }
    }

    // 8 special points need to specified
    for( int k = tempGridsCellLevel; k < fieldsGridsSize - tempGridsCellLevel +1; k++)
    {
// On face 0
//
        Btemp = ptrBVectorFaceArray[0][0][0][0][k-1].PlusProduct(
            ptrBVectorFaceArray[1][0][0][0][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][4][fieldsGridsSize][0][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][0][0][0][k]).PlusProduct(
                        ptrBVectorFaceArray[1][0][0][0][k]).PlusProduct(
                            ptrBVectorFaceArray[1][4][fieldsGridsSize][0][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[0][1][1][k]->SetdB3(Btemp);

        Btemp = ptrBVectorFaceArray[0][0][fieldsGridsSize][0][k-1].PlusProduct(
            ptrBVectorFaceArray[1][0][fieldsGridsSize][0][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][1][0][0][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][0][fieldsGridsSize][0][k]).PlusProduct(
                        ptrBVectorFaceArray[1][0][fieldsGridsSize][0][k]).PlusProduct(
                            ptrBVectorFaceArray[1][1][0][0][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[0][fieldsGridsSize+1][1][k]->SetdB3(Btemp);
        
        Btemp = ptrBVectorFaceArray[0][0][0][fieldsGridsSize][k-1].PlusProduct(
            ptrBVectorFaceArray[1][0][0][fieldsGridsSize][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][4][fieldsGridsSize][fieldsGridsSize][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][0][1][fieldsGridsSize][k]).PlusProduct(
                        ptrBVectorFaceArray[1][0][1][fieldsGridsSize][k]).PlusProduct(
                            ptrBVectorFaceArray[1][4][fieldsGridsSize][fieldsGridsSize][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[0][1][fieldsGridsSize+1][k]->SetdB3(Btemp);

        Btemp = ptrBVectorFaceArray[0][0][fieldsGridsSize][fieldsGridsSize-1][k-1].PlusProduct(
            ptrBVectorFaceArray[1][0][fieldsGridsSize-1][fieldsGridsSize][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][1][0][fieldsGridsSize][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][0][fieldsGridsSize][fieldsGridsSize][k]).PlusProduct(
                        ptrBVectorFaceArray[1][0][fieldsGridsSize][fieldsGridsSize][k]).PlusProduct(
                            ptrBVectorFaceArray[1][1][0][fieldsGridsSize][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[0][fieldsGridsSize+1][fieldsGridsSize+1][k]->SetdB3(Btemp);

// On face 3
        Btemp = ptrBVectorFaceArray[0][3][0][0][k-1].PlusProduct(
            ptrBVectorFaceArray[1][3][0][0][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][1][fieldsGridsSize][0][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][3][0][0][k]).PlusProduct(
                        ptrBVectorFaceArray[1][3][0][0][k]).PlusProduct(
                            ptrBVectorFaceArray[1][1][fieldsGridsSize][0][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[3][1][1][k]->SetdB3(Btemp);

        Btemp = ptrBVectorFaceArray[0][3][fieldsGridsSize][0][k-1].PlusProduct(
            ptrBVectorFaceArray[1][3][fieldsGridsSize][0][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][4][0][0][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][3][fieldsGridsSize][0][k]).PlusProduct(
                        ptrBVectorFaceArray[1][3][fieldsGridsSize][0][k]).PlusProduct(
                            ptrBVectorFaceArray[1][4][0][0][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[3][fieldsGridsSize+1][1][k]->SetdB3(Btemp);
        
        Btemp = ptrBVectorFaceArray[0][3][0][fieldsGridsSize][k-1].PlusProduct(
            ptrBVectorFaceArray[1][3][0][fieldsGridsSize][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][1][fieldsGridsSize][fieldsGridsSize][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][3][0][fieldsGridsSize][k]).PlusProduct(
                        ptrBVectorFaceArray[1][3][0][fieldsGridsSize][k]).PlusProduct(
                            ptrBVectorFaceArray[1][1][fieldsGridsSize][fieldsGridsSize][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[3][1][fieldsGridsSize+1][k]->SetdB3(Btemp);

        Btemp = ptrBVectorFaceArray[0][3][fieldsGridsSize][fieldsGridsSize][k-1].PlusProduct(
            ptrBVectorFaceArray[1][3][fieldsGridsSize][fieldsGridsSize][k-1]).PlusProduct(
                ptrBVectorFaceArray[1][4][0][fieldsGridsSize][k-1]).PlusProduct(
                    ptrBVectorFaceArray[0][3][fieldsGridsSize][fieldsGridsSize][k]).PlusProduct(
                        ptrBVectorFaceArray[1][3][fieldsGridsSize][fieldsGridsSize][k]).PlusProduct(
                            ptrBVectorFaceArray[1][4][0][fieldsGridsSize][k]).ScaleProduct( 1.0 / 6.0);    
        ptrArray[3][fieldsGridsSize+1][fieldsGridsSize+1][k]->SetdB3(Btemp);
    }
}
