#include "./nul.h"
#include <stdlib.h>



int NulObject::Draw ()
{

return 0;
}

int NulObject::Calc ()
{
//PF.Calc();

return 0;
}



vec2 NulObject::GetCord ()
{
return PF.cord;
}

vec2 *NulObject::GetUCord ()
{
return &PF.cord;
}




