## Система выделения памяти


## Обший класс менеджер
class Allocator:
init():
setMaxMemory(): 



### Init()
Real memory = Get to OS 20% RAM: 
Reserve virtual adress = 100% * 4;


#### In memory structure

Allocator:
    
uint8_t ptr on start;
size_t max_size;



Our size = max_size;
-------------------------------------
get ofs on start 
  -----
    |
    |->    linear allocator <--                   
    |
    |->    pool allocator <--
    |
    |->    stack allocator <--
    |
    |->    free list allocator <-- 
-------------------------------------
   

PRIVATE ->
    alignment memory;

API -> 
    
    new (memory type,sizeof(struct)) -> uint8_t ptr 

    free (memory type,uint8_t ptr) -> void






#1 linear )
## Нужно для хранения быстрой и однокадровой памяти

start ptr;
max_size;
cursor ptr;
           
                                max_size
[][][][][][][][][][][][][][][]....->

------
    allocate new memory (example = 24b)
        |
        v 
    create ptr;
    cursor += 24b  
    return ptr;

------
    free memory ()
    reset all linear plate 




#2 pool )
## Для хранения быстрой памяти с возможностью выборочного очищения,огр макс размер

Pool Manager:
start ptr;
max_size:

Object Pool 
-------> 1 linear

ptr start;
max_count cell = ...
size cell > 8b = ...
m_head ptr = start;

[size cell] [...] [...] [...] [...] -> max_count cell 
              /
             /
            /
           /
        [] default = next ptr:
        



API Pool Manager  
    |
    create plate (sizeof(structure),max capacity) -> ID
    |
    delete plate(ID)

API Object Pool 
    |
    allocate new memory (size) -> ptr 
        ptr = copy res_m_head  ->
        m_head = m_head->next 
        return ptr;
    |
    free memory (ptr);
        ptr->next = copy m_head;
        m_head = ptr; 





#3 stack )

## Для обьектов разных размеров и быстрой но порядкового очищения(LIFO структура) 


##Stack Manager )
    stack queue <ID markers>;  
    task queue <>;
    cursor ptr:
    start ptr:
    max_size:

    API -> 

        create plate () -> ID 
            
        free plate (ID) ->  
        


##Stack Object )
    ID marker;
    start ptr;
    max_size;
    cursor ptr; 

    [000][00000][00][000][00000]...->
    
    

### Stack manager 16gb 

Logic 
[][][][][][]...

Physix
[][][][]...

Graphics
[][][][][][][][][][]...

> Stack manager used X tick manager,sync all created plate in `Диспетчер памяти`



#4 free list )


## Нужен для обьектов разных размеров в разных местах, блоки памяти могут увеличиватся

```
struct BlockHeader{
    size block_size;
    bool is_free;
    BlockHeader* next;
}
```

FreeList Manager:
size;
start ptr;

Block Object {size,is_free = true}
---->
[head][][][][][][][][][][][][][][][][][][][][][]


Allocate new (size)
    //Best fit schemes
    
[head][][][][][][][][][][][][][][][][][]...
        |
        |
        v 
        
        free = false    |free = true
    [new head][][][][][]|[head][][][][][][][][][]...
       /
      /
     /
return ptr 
    
Deallocate free (ptr) 
    head_ptr = ptr - sizeof(header Object)
    head_ptr->free = true;

> Слияние при фрагментации памяти;


[200][200][....]
    \
     \
      \
    [200]+[200]
        \
         \
         [400]

> if free blocks nearby: they merge



> Вопрос с расширением блока:

:Reserve virtual memory,

:Preload memory on init










#Логика мастшабирования в общем Аллокаторе 
---

linear  segment         
[x][x][][][][][][][][][][][][]... 

pool segment      
[x][x][x][x][x][][][][][][][][]... 

stack segment       
[x][][][][][][][][][][][][][]... 

free list segment
[x][x][x][][][][][][][][][]... 



-----------
[][]... <- reserve memory (no real impact)
-----------

-----------
[x][x]... <- real use memory (real impact)
-----------


### example:
If linear segment overflow real memory:
    OS get more real memory
    // linear segment think that nothing has changed
---
















Одноразовый мусор кадра, логи, матрицы трансформаций UI: Linear Allocator (Сброс каждый тик).

Тысячи компонентов ECS, патроны, одинаковые FixedVector: Pool Allocator (Точечное удаление, скорость $O(1)$)..

Загрузка сцен, уровней, тяжелые асинхронные буферы файлов:Stack Allocator (Порядковое удаление LIFO).

Хэш-таблицы кэша, динамические строки, разношерстные менеджеры: Free List Allocator (Полная свобода действий для сложных структур).























