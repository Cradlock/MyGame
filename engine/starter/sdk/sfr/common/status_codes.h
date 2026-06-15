#pragma once 


// Общие коды ошибок 
typedef enum sfr_result_code_e {
  SFR_SUCCESS,            // успешно
   SFR_NOT_FOUND,          // Не найдено 
   SFR_INVALID_PARAMETR,   // Неправильные аргументы
   SFR_INVALID_PATH,       // Неправильный путь
   SFR_UNKNOW_EXTENSION,   // Неизвестный тип
   SFR_CREATED_NEW,        // Создан новый обьект
   SFR_UNKNOW_ACTION,      // Неизвестное действие
   SFR_WRONG_TYPE,         // Неправильный тип
   SFR_OUT_OF_RANGE,       // Выходит за границы
   SFR_OBJECT_ERROR_STATE, // Обьект не может сделать действие

   SFR_UNKNOW_ERROR,       // Неизвестная ошибка
   SFR_UNCOMPATABLE_ACTION,// Действие не поддерживается
   SFR_IO_ERROR,           // Техническая ошибка ввода-вывода 
   SFR_SEEK_ERROR,         // Ошибка перехода курсора 

} sfr_result_code_t;


