#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>


TEST(ProgramTest, TestTest) {
    const char* temp_input_file = "temp_input.txt";

    std::ofstream input_file(temp_input_file);

    input_file << "output.txt" << std::endl; 
    input_file << "3.14 2.0 1.0" << std::endl; 
    input_file.close();

    
    std::string command = "./parent < " + std::string(temp_input_file);
    system(command.c_str());

   
    std::remove(temp_input_file);

    std::ifstream infile("output.txt");
    float sum;

    infile >> sum;
    infile.close();

    EXPECT_NEAR(sum, 6.14, 0.001);
}