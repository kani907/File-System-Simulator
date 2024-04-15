set(FILES file.cpp folder.cpp fileManager.cpp)
add_library(FilesData ${FILES})
add_executable(main main.cpp ${FILES})