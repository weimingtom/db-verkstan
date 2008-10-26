#include "cli/SineClip.hpp"

#include "cli/ClipFactory.hpp"

namespace Verkstan
{
    Clip^ ClipFactory::Create(String^ name)
    {
        if (name == "Sine")
        {
            Core::Clip* c = new Core::SineClip();

            int id;                                    
            for (int i = 0; i < DB_MAX_CLIPS; i++)
            {                                        
                if (Core::clips[i] == 0)
                {                                     
                    Core::clips[i] = c; 
                    id = i;                          
                    break;                            
                }                                     
            }    
            return gcnew SineClip(id);
        }

        return nullptr;
    }
}