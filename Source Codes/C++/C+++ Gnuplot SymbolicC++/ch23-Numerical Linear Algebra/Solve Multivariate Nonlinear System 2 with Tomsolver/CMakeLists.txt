
file(GLOB TEST_CODE
	*.cpp
	)

add_executable(result ${TEST_CODE})

target_include_directories(result PUBLIC
	../../single/include
	)
