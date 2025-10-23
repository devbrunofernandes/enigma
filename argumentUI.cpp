#include "argumentUI.hpp"
#include <exception>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "cxxopts.hpp"
#include <fstream>

void processStream(Enigma &en, std::istream &inStream, std::ostream &outStream) {
    std::stringstream buffer;
    buffer << inStream.rdbuf();
    std::string input = buffer.str();
    std::string output = en.encodeText(input);
    outStream << output;
}

std::vector<std::string> parseRotors(std::string rotors) {
    std::vector<std::string> result;
    std::string singleRotor;

    std::istringstream iss(rotors);

    while(iss >> singleRotor) {
        result.push_back(singleRotor);
    }
    return result;
}

void argumentMode(int argc, char* argv[], bool stdinIsTty) {
    cxxopts::Options options("Enigma-Machine", "CLI Simulator for Enigma encryption machine used in WW2.");

    options.add_options()
        ("f,file", "Input file name", cxxopts::value<std::string>())
        ("o,output", "Output file name", cxxopts::value<std::string>())
        ("rotors", "Rotors to use in order (ex: \"I II III\")", cxxopts::value<std::string>()->default_value("I II III"))
        ("p,positions", "Initial position of rotors", cxxopts::value<std::string>()->default_value("AAA"))
        ("r,reflector", "Used reflector", cxxopts::value<std::string>()->default_value("B"))
        ("plugboard", "Plugboard connections", cxxopts::value<std::string>()->default_value(""))
        ("h,help", "Print usage")
    ;

    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            exit(0);
        }

        EnigmaConfig config;

        config.rotorNames = parseRotors(result["rotors"].as<std::string>());
        config.rotorInitial = result["positions"].as<std::string>();
        config.reflector = result["reflector"].as<std::string>();
        config.plugboardConnections = result["plugboard"].as<std::string>();

        Enigma en(config);

        // has input validation
        bool has_file_input = result.count("file");
        bool stdin_is_pipe = !stdinIsTty;

        if (!has_file_input && !stdin_is_pipe) {
            std::cerr << "ERROR: Input text not found." << std::endl;
            std::cerr << "Use -f <file> or give input values by pipe (ex: echo '...' | ./enigma_machine ...)" << std::endl;
            std::cerr << "\n" << options.help() << std::endl;
            exit(1);
        }

        // input open file
        std::ifstream inFile;
        if(result.count("file")) {
            inFile.open(result["file"].as<std::string>());
            if(!inFile.is_open()) {
                throw std::runtime_error("Could not open input file '" + result["file"].as<std::string>() + "'");
            }
        }
        std::istream& inStream = result.count("file") ? inFile : std::cin;

        // output open file
        std::ofstream outFile;
        if(result.count("output")) {
            outFile.open(result["output"].as<std::string>());
            if(!outFile.is_open()) {
                throw std::runtime_error("Could not open output file '" + result["file"].as<std::string>() + "'");
            }
        }
        std::ostream& outStream = result.count("output") ? outFile : std::cout;

        processStream(en, inStream, outStream);
    } catch (const cxxopts::exceptions::exception& e) {
        std::cerr << "ARGUMENT ERROR: " << e.what() << std::endl;
        std::cerr << "Use -h or --help to see all valid options." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}