# Работа с ресурсами


### Ресурсный менеджер:
    |
    |=========> Хранилище (Хеш-таблица: Ресурс[путь] )
    |
    |=========> Список провайдеров (Массив: Провайдер) 
    |
    |=========> Хранилище таблиц функций (Хеш-таблица: Структура Функций[GUID типа] ) 
    |
    |=========> Хранилише типов ресурсов (Хеш-таблица: ID типа[Название типа])
    |
    |=========> Селекторы(Способы определения файла)
    |       
    |       :==> Extensions (Хеш-таблица: (Вектор:ID типa)[Расширение])
    |
    |       :==> MagicBytes (Хеш-таблица: (Векторы:ID типа)[Байты])
    |
    |       :==> HeavyFallback (Хеш-таблица: (Istream) => boolean[ID типа]
    |
    |=========> Очередь задач (Очередь: Обьект задачи)
    |
    |=========> Очередь готовых задач (Очередь: Обьект задачи Нужен потому что видеокарта обшается только с главным потоком)
    |
    |=========> Пул потоков (Вектор: Обьект потока)
    |
    |=========> Мьютекс (связан в очередью задач)
    |
    |=========> Флаг остановки (atomic<Булевый тип> Нужен для корректного завершения всех потоков) 
    |
    |=========> Сигнал (Привязан к потокам Нужен для контроля работы потоков)
    
    

## Инициализация
1. Определения количества для `Пула потоков`



## Провайдер 
Класс для работы с источником ресурсов(файлов) \
### Istream
Istream - общий класс-интерфейс, который выдает доступ к байтам. \
Возможные дочерние-классы: 
* class FileStream : public Istream{};
* class WebStream : public Istream{};
* class ZipStream : public Istream{}; \
Виртуальные обязательные функции: \
Чтение: \
`ResUsedBytes (*read)(IStream* self,void* buffer,size_t size);`
Запись: \
`ResUsedBytes (*write)(IStream* self, const void* buffer, size_t size);`
Перемещение курсора: \
`ResOffsetBytes (*seek)(IStream* self, int64_t offset, int origin);`
Узнать текушую позицию курсора: \
`ResSize (*tell)(IStream* self);`
Обший размер: \
`ResSize (*size)(IStream* self);`
Правилность ресурса: \
`ResValid   (*is_valid)(IStream* self);`
Закрытие потока: \
`void   (*close)(IStream* self);`


### Ресурс
Класс деляшийся на две части: \

### Внутренний ресурс
```
class ResourceInternal:
Resource pub;
Metadata{
    Path fullpath;
    int ref_count;
    State state;
}
ResourceVtable vtable{
    create;
    load;
    save;
    release;
    finalize;
};
ID resource_type;
```

### Внешний ресурс
```
Resource:
void* data;
```


### Регистрация типов
```
.h]
class JsonNode:
    ...

class JsonResource : public Resource:
    JsonNode* data;

.{lang}]
rcm->register_type({
    name:"json",
    selector: {
        ext: ".json",magicBytes: nullptr,HeavyFallback:boolean (*check)(Istream)
    },
    vtable: {
        *load,*create,*save,*release
    }
})
```
============
    \
     \ props = {name,selector,vtable}
      \
    ID = generate_ID()
    Типы ресурсов[dynamic libname + name] = ID 
    Функции[ID] = vtable
    Селекторы[selector...] = ID
    ---------------
    Если одинаковые имена или файлы: то отключение и FATAL ошибка в логах
   




Использование: 
```
JsonResource* config = rcm->load("assets/player.json",SYNC,"json:json");

Texture* player = rcm->create("",ASYNC,"graphics:texture2D");
player->set(12321....);
rcm->save(player,ASYNC);
```







## Процесс загрузки ресурса
0. Создание Пустого ресурса (
    if type_props: 
        if type_props not find:
            state = "undefined type" stop
        Resource res(type_finded)
    Resource res 
)

1. Выбор провайдера (
    For(providers){
        select provider;
        if success and suppoer task_type : return provider;
    }
)

2. Выбор режима (добавление задачи) (
    Task create(res,provider,provider.stream)
    
    if SYNC:
        go 3.
    if ASYNC:
        Add task (task)
)

3. Обработка задачи process_task:

    1. Тип ресурса (
    candidates = []
        find on extensions(
            find one -> 2.
            find some : add candidates
            not finded -> next 
        )
        find on magicBytes(
            task.stream.seek(0)
            magicBytes[candidates...].for(
                task.stream 
            )
            candidates one -> 2.
            candidates some -> next 
            not finded -> magicBytes.for( res.stream ) 
                not find -> next 
                find one -> 2.
                find some -> add candidates,next 
        )

        find on HeavyFallback(
            task.stream.seek(0)
            final_candidates = []
            for(HeavyFallbacks[candidates...]){
                if elem(task.stream):final_candidates add(ID)
            }
            find one in final_candidates -> 2.
            not find -> state = undefined type 
            find some -> state = cross type 
        )

    )

    2. Активация задачи (
        task.stream(0)
        Type ID;
        Resource res = task.get_res();
        Vtable vtable = vtables.find(ID)
        switch (task.type_task) case... vtable...(task.stream);
    )

    3. Вставка задачи из доп потока в основной поток. (tasks_ready)


## Работа потоков 


Main thread
-------------------------------------------------------->
        
        th(1)   loop
        --------------------->

        th(2)   loop 
        --------------------->

        th(3)   loop 
        ---------------------X


In Main thread:
mtx start
    tasks.add()    
mtx stop 
      |
    cv.notify_one() 
            \
             \
              \
               \
            CV (OS)  Select one thread and start it

th(3) start

    th(3)    loop 
    -------------------->
    

loop(
    Task ts
    {
       mtx lock;
       cv.wait(lock,[] () {
            return stop_pool || !tasks.empty();
       })

        ts = tasks.front();
        tasks.pop();
    }

    process_task(ts)
)





## ready_tasks 
Очередь готовых задач которая использует `finalize` из vtable 
> Проходит в главном потоке




































