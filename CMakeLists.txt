cmake_minimum_required(VERSION 2.8) #Проверка версии CMake.

set(PROJECT_NAME s4_Lab1_AlgPol) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME} ) # Название проекта

set(polinom polinom) #Переменная с именем библиотеки
set(testfiles testfiles)
set(table table)
set(Interface Interface)
set(calculator calculator)


set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) #Создается переменная CMAKE_CONFIGURATION_TYPES со значением "Debug;Release" и меткой/разделом Configs, переменная сохраниется в специальном файле доступном из всех файлов,
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/table)
add_subdirectory(table)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/polinom) 
add_subdirectory(polinom)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/testfiles) 
add_subdirectory(testfiles)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Interface)
add_subdirectory(Interface)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/calculator)
add_subdirectory(calculator)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
add_subdirectory(gtest)

#file(GLOB hdrs "*.h*") #Добавляем в переменную hdrs все файлы с расширением .h
#file(GLOB srcs "*.cpp") #Добавляем в переменную srcs все файлы с расширением .cpp
