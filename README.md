# Udacity C++ Nano Degree
Projects from Udacity's C++ Nano degree 2022

## Project #1: Build an OpenStreetMap Route Planner

### Building
To build the code, make a build directory into the project and then cd into that directory. From within the build directory, you can then run the following commands to compile:

  cmake ..
  make
  
### Running
Once the build is complete, the executable binary files will be in the build folder of the project, and the project will be ready to run.
Running the project must be done from the workspace desktop in order for you to be able to see the mapped output. In the terminal, navigate to the build folder. 
From the build directory, you can run the compiled executable with map data using the following command:

./OSM_A_star_search

Or to specify a map file:
./OSM_A_star_search -f ../<your_osm_file.osm>
