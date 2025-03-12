#include "UBuffer.hpp"
#include <memory.h>
#include <string.h>

/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
namespace Game{
    UBuffer::UBuffer(
              u32  count                , 
              u32  size                 ,  
        alloc allocateFunction          , 
        dalloc dallocateFunction        )
    {
        //check parameters
        ASSERT(size , "The Size of the uniform buffer is defined zero !");
        ASSERT(count, "The number of uniforms can not be zero !");
        ASSERT(allocateFunction , "No Allocation function is given !!!");
        ASSERT(dallocateFunction, "No Free Function is Given");
        
        //Even if parameters are bad still define a default behavor even if is not right
        if (allocateFunction == nullptr)
            allocateFunction = malloc;
        if (dallocateFunction == nullptr)
            dallocateFunction = free;
        if (size == 0 ) 
            size = 128;   
        if (count == 0) 
            count= 24;
        
        //Initiallize all variables and allocate the space needed for each
        m_Malloc = allocateFunction;
        m_Free   = dallocateFunction;
        m_Size = size;
        m_CountUniforms = count;
        m_SpecifiedUniforms = 0;//no uniform is added yet
        m_HasMoved = false;
        ;
        
        // allocate the total size for the uniforms data from cpu side
        m_UniformsMemory = m_Malloc(size);
        ASSERT(m_UniformsMemory , "No memory !");
        m_MemCurrent = m_UniformsMemory;
        
        // allocate count uniform type definitions
        m_UniformsTypes = (UniformType*)m_Malloc(m_CountUniforms*sizeof(UniformType));
        ASSERT(m_UniformsTypes , "No Memory !!!");

        // allocate count uniform offset's for define with each uniform add method 
        m_UniformsOffsets = (u64*)m_Malloc(m_CountUniforms*sizeof(u64));
        ASSERT(m_UniformsOffsets , "No Memory !!!");

        // allocate count string pointers for each uniform name
        m_UniformsNames = (char**)m_Malloc(m_CountUniforms*sizeof(char*));
        ASSERT(m_UniformsNames , "No Memory !!!");

        // allocate count u32 number's for each uniform name length
        m_NamesLength = (u32*)m_Malloc(m_CountUniforms*sizeof(u32));
        ASSERT(m_NamesLength , "No Memory !!!");

        //all allocation's are ready for use now
    }

    UBuffer::UBuffer(UBuffer&& move){
        m_Malloc            = move.m_Malloc;
        m_Free              = move.m_Free;
        m_NamesLength       = move.m_NamesLength;
        m_UniformsNames     = move.m_UniformsNames;
        m_UniformsOffsets   = move.m_UniformsOffsets;
        m_UniformsTypes     = move.m_UniformsTypes;
        m_SpecifiedUniforms = move.m_SpecifiedUniforms;
        m_CountUniforms     = move.m_CountUniforms;
        m_Size              = move.m_Size;
        m_UniformsMemory    = move.m_UniformsMemory;
        m_HasMoved          = false;
        m_MemCurrent        = move.m_MemCurrent;

        move.m_Malloc               = nullptr   ;
        move.m_Free                 = nullptr   ;
        move.m_NamesLength          = nullptr   ;
        move.m_UniformsNames        = nullptr   ;     
        move.m_UniformsOffsets      = nullptr   ;
        move.m_UniformsTypes        = nullptr   ;
        move.m_SpecifiedUniforms    = 0         ;
        move.m_CountUniforms        = 0         ;
        move.m_Size                 = 0         ;
        move.m_UniformsMemory       = nullptr   ;
        move.m_HasMoved             = true      ;
        move.m_MemCurrent           = nullptr   ;
    }

    UBuffer& UBuffer::operator=(UBuffer&& move){
        m_Malloc            = move.m_Malloc;
        m_Free              = move.m_Free;
        m_NamesLength       = move.m_NamesLength;
        m_UniformsNames     = move.m_UniformsNames;
        m_UniformsOffsets   = move.m_UniformsOffsets;
        m_UniformsTypes     = move.m_UniformsTypes;
        m_SpecifiedUniforms = move.m_SpecifiedUniforms;
        m_CountUniforms     = move.m_CountUniforms;
        m_Size              = move.m_Size;
        m_UniformsMemory    = move.m_UniformsMemory;
        m_HasMoved          = false;

        move.m_Malloc               = nullptr  ;
        move.m_Free                 = nullptr  ;
        move.m_NamesLength          = nullptr  ;
        move.m_UniformsNames        = nullptr  ;
        move.m_UniformsOffsets      = nullptr  ;
        move.m_UniformsTypes        = nullptr  ;
        move.m_SpecifiedUniforms    = 0        ;
        move.m_CountUniforms        = 0        ;
        move.m_Size                 = 0        ;
        move.m_UniformsMemory       = nullptr  ;
        move.m_HasMoved             = true;

        return *this;
    }

    UBuffer::~UBuffer(void){
        if (m_HasMoved)
            return;
        //free the memory of the uniform data
        if (m_UniformsMemory)
            m_Free(m_UniformsMemory);
        //free the memory of the names length for each uniform
        if (m_NamesLength)
            m_Free(m_NamesLength);
        //free the memory from all names of each uniform and the double ptr
        if (m_UniformsNames){
            for (int i  = 0 ; i < m_CountUniforms; i++)
                if  (m_UniformsNames[i])
                    m_Free(m_UniformsNames[i]);
            m_Free(m_UniformsNames);
        }
        //free uniforms offset
        if (m_UniformsOffsets)
            m_Free(m_UniformsOffsets);
        //free uniforms types
        if (m_UniformsTypes)
            m_Free(m_UniformsTypes);
        // all freed
    }

}




/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/


namespace Game{
    u32 GetUniformTypeSize(UniformType utype){
        switch(utype){
            case UniformType::SAMPLER_2D        :   return sizeof(unsigned int);
            case UniformType::ISAMPLER_2D       :   return sizeof(unsigned int);
            case UniformType::USAMPLER_2D       :   return sizeof(unsigned int);
            case UniformType::UNSIGNED_INT      :   return sizeof(unsigned int);
            case UniformType::VEC3F             :   return 3*sizeof(float);
            case UniformType::VEC4F             :   return 4*sizeof(float);
            case UniformType::MAT4F_T           :   return 4*4*sizeof(float);
            default:
                ASSERT(0 , "Undefined Uniform Type !!!");

        }
        return 0;
    }
}


















/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/
/*==================================================================================
/*==================================================================================*/
/*==================================================================================*/




namespace Game{
    
    u32 UBuffer::GetUniformsCount(void) const{
        return m_CountUniforms;
    }
    /*return the total uniforms this ubuffer can have*/
    u32 UBuffer::GetDefinedUniformsCount(void) const{
        return m_SpecifiedUniforms;
    }
    /*return the total uniforms this ubuffer have take*/
    u32 UBuffer::GetUndefinedUniformsCount(void) const{
        return m_CountUniforms - m_SpecifiedUniforms;
    }
    /*return the total uniforms this ubuffer can take*/
    bool UBuffer::AddUniform(UniformType type , char* name , u32 length , void* data ){
        if (m_HasMoved){
            ASSERT(0 , "This Uniforms Buffer has move its contents to other ubuffer !!!");
            return false;
        }

        if (name == nullptr){
            ASSERT(0 , "Can't add a uniform without a name !!!");
            return false;
        }

        if (m_SpecifiedUniforms >= m_CountUniforms){
            ASSERT(0 , "Uniform's Buffer is full !!!");
            return false;
        }

        void* alligmentPos  = m_MemCurrent;
        u64   TypeSize      = GetUniformTypeSize(type);
        u64   Modulo        = ((u64)alligmentPos) % TypeSize;
        u64   ExtraCount    = (Modulo) ? (TypeSize - Modulo) : 0;
        alligmentPos        = m_MemCurrent + ExtraCount;
        if ((alligmentPos + TypeSize) > (m_UniformsMemory + m_Size)){
            ASSERT(0 , "No Enough Uniform Data Space to add a new uniform !!!");
            return false;
        }
        m_MemCurrent = alligmentPos + TypeSize; 
        if (data != nullptr)
            memcpy(alligmentPos , data , TypeSize);
        
        
        m_SpecifiedUniforms++;

        m_UniformsOffsets[m_SpecifiedUniforms - 1] = (u64)alligmentPos;

        m_NamesLength[m_SpecifiedUniforms - 1] =(length) ? (length+1) : (strlen(name) + 1);
        
        m_UniformsNames[m_SpecifiedUniforms - 1] 
        = (char*)m_Malloc(m_NamesLength[m_SpecifiedUniforms - 1 ] );

        strncpy(
            m_UniformsNames[m_SpecifiedUniforms - 1] , name ,
            m_NamesLength[m_SpecifiedUniforms - 1] - 1 );

        char* Uname = m_UniformsNames[m_SpecifiedUniforms - 1];
        Uname[m_NamesLength[m_SpecifiedUniforms - 1] - 1] = '\0';
        
        m_UniformsTypes[m_SpecifiedUniforms - 1] = type;
        
        return true;
    }


    u32 UBuffer::GetUniformIdByName(const char* name) const{
        if (m_HasMoved){
            ASSERT(0 , "This Uniforms Buffer has move its contents to other ubuffer !!!");
            return 0xFFFFFFFF;
        }

        if (m_SpecifiedUniforms == 0){
            ASSERT(0 , "No Uniforms have added yet !!!");
            return 0xFFFFFFFF;
        }

        u32 id = 0xFFFFFFFF;
        u32 length = strlen(name);
        for(u32 i = 0; i < m_SpecifiedUniforms; i++){
            u32 minSize = length;
            if (minSize < m_NamesLength[i])
                minSize = m_NamesLength[i];

            if (strncmp(m_UniformsNames[i] , name, minSize)){
                id = i;
                break;
            }
        }

        return id;
    }
    void* UBuffer::GetUniformLocationByName(const char* name) const{
        u32 id = GetUniformIdByName(name);

        if (id == 0xFFFFFFFF){
            ASSERT(0 , "Uniform Can't found !!!");
            return nullptr;
        }
        
        return (void*)m_UniformsOffsets[id]; 
    }

    UniformType UBuffer::GetUniformTypeByName(const char* name) const{
        u32 id = GetUniformIdByName(name);

        if (id == 0xFFFFFFFF){
            ASSERT(0 , "Uniform Can't found !!!");
            return (UniformType)0;
        }

        return m_UniformsTypes[id];
    }
                
}





