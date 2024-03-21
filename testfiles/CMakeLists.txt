file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(${testfiles} ${srcs} ${hdrs}) 

target_link_libraries(${testfiles} ${table} ${polinom} ${calculator}) #Подключаем к проекту с именем ${vector} библиотеки с именами ${vectorlib} и gtest
