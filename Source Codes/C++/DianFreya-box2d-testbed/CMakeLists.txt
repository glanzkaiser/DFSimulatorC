set (TESTBED_SOURCE_FILES
	draw.cpp
	draw.h
	imgui_impl_glfw.cpp
	imgui_impl_glfw.h
	imgui_impl_opengl3.cpp
	imgui_impl_opengl3.h
	main.cpp
	settings.h
	settings.cpp
	test.cpp
	test.h
	tests/test.cpp
	tests/stir_liquid.cpp
	tests/circular_motion.cpp
	tests/circular_motionbox.cpp
	tests/circular_motionairplane.cpp
	tests/projectile_motion.cpp
	tests/projectile_dropped.cpp
	tests/kineticenergy_collision.cpp	
	tests/work_cratependulum.cpp	
	tests/kineticenergy_work.cpp	
	tests/work_conveyorbelt.cpp
	tests/work_gravitationalforce.cpp
	tests/work_pulleyelevator.cpp	
	tests/work_generalvariable.cpp	
	tests/work_verticalspringupward.cpp	
	tests/spring_work.cpp
	tests/conservationofenergy_blockslidestohigherlevel.cpp
	tests/conservationofenergy_particleslidestillstop.cpp
	tests/conservationofenergy_elevatorsnaps.cpp
	tests/potentialenergy_looptheloop.cpp
	tests/potentialenergy_verticalspringupward.cpp
	tests/potentialenergy_runawaytruck.cpp
	tests/potentialenergy_springincline.cpp
	tests/potentialenergy_marblespringgun.cpp
	tests/centerofmass_airplaneexplosion.cpp
	tests/centerofmass_atomicbomb.cpp
	tests/centerofmass_bulletshotupward.cpp
	tests/centerofmass_elasticcollisionsteelball.cpp
	tests/centerofmass_elasticcollisiontwoballs.cpp
	tests/centerofmass_threeparticles.cpp
	tests/centerofmass_racecarwallcollision.cpp
	tests/centerofmass_speeddeamplifier.cpp
	tests/centerofmass_speedamplifier.cpp
	tests/spring_test.cpp
	tests/spring_twomasses.cpp
	tests/verticalspring_test.cpp
	tests/newton_firstlaw.cpp
	tests/newton_firstlaw2dforces.cpp
	tests/pulley_jointtriangle.cpp
	tests/pulley_kineticfriction.cpp
	tests/dragforce_skier.cpp
	tests/frictional_forces.cpp
	tests/gases_container.cpp
	tests/gravity_check.cpp
	tests/simple_pendulum.cpp
	tests/angular_oscillator.cpp
)

add_executable(testbed ${TESTBED_SOURCE_FILES})
target_include_directories(testbed PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(testbed PUBLIC box2d glfw imgui sajson glad)
set_target_properties(testbed PROPERTIES
	CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# message(STATUS "runtime = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
# message(STATUS "binary = ${CMAKE_CURRENT_BINARY_DIR}")

# Copy font files, etc
add_custom_command(
        TARGET testbed POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/data/
                ${CMAKE_CURRENT_BINARY_DIR}/data/)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TESTBED_SOURCE_FILES})
