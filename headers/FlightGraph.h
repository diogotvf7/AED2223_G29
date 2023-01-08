//
// Created by diogotvf7 on 29-12-2022.
//

#ifndef AED2223_G29_FLIGHTGRAPH_H
#define AED2223_G29_FLIGHTGRAPH_H

#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include "City.h"
#include "Country.h"

class Airport;
class Country;
class City;

typedef std::unordered_map<std::string, Airline*> UMairlines;
typedef std::unordered_map<std::string, Airport*> UMairports;
typedef std::unordered_map<std::string, City*> UMcities;
typedef std::unordered_map<std::string, Country*> UMcountries;

class FlightGraph {
    UMairlines airlines;
    UMairports airports;
    UMcountries countries;
    UMcities cities;

public:
    /**
     * @brief Constructor for the FlightGraph class
     * @param airports the Airport's unordered_map
     * @param airlines the Airline's unordered_map
     * @param countries the Country's unordered_map
     * @param cities the City's unordered_map
     */
    FlightGraph(UMairports &airports, UMairlines &airlines, UMcountries &countries, UMcities &cities);
    /**
     * @brief This function adds a Flight to the source Airport with target to {target} and using {airline} as it's Airline
     * @param source a pointer to the source's Airport
     * @param target a pointer to the target's Airport
     * @param airline a pointer to the Flight's Airline
     */
    void addFlight(Airport *source, Airport *target, Airline *airline);
    /**
     * @brief Depth-First Search algorithm
     * @param airport the source Airport's code
     */
    void dfs(const std::string &airport);
    /**
     * @brief This function is a dfs that stores all the traversed nodes in a vector
     * @param airport the source Airport's code
     * @param vairports the vector of the traversed Airport's code
     * @param filter this optional argument will be ignored if the list is empty. In case it's not, only Flights using the Airlines inside the list will be considered
     */
    void listComponent(const std::string &airport, std::vector<std::string> &vairports, std::list<Airline*> filter = {});
    /**
     * @brief This function finds the articulation points of the graph starting from {airport} and stores them on {artAirports}
     * @param airport the source Airport's code
     * @param order traversal order value
     * @param artAirports list with the articulation Airports
     */
    void articulationAirports(const std::string &airport, int &order, std::list<Airport*> &artAirports);
    /**
     * @brief This function finds the strongly connected components of the graph starting from {airport} and stores them on {sccs}
     * @param airport the source Airport's code
     * @param s a stack that stores the scc Airport's until needed
     * @param order traversal order value
     * @param sccs a list of all the strongly connected components
     */
    void stronglyConnectedComponents(const std::string &airport, std::stack<Airport*> &s, int &order, std::list<std::list<Airport*>> &sccs);
    /**
     * @brief This function is a Breadth-First Search that changes every Airport's distance field to it's distance (in number of Flights) from the {source} airport
     * @param source the source Airport's code
     */
    void countFlights(const std::string &source);
    /**
     * @brief This function implements the Dijkstra min distance algorithm and changes every Airport's distance field to it's distance (in km) from the {source} airport
     * @param source the source Airport's code
     */
    void dijkstra(const std::string &source);
    /**
     * @brief This function checks which Airports, Countries or Cities can be reached from {source} using at most n Flights, it can also check which Airlines can be used in at most n Flights
     * @param source the the source Airport's code
     * @param n the maximum number of Flights
     * @param mode mode = 0 -> output considering airports; mode = 2 -> output considering countries; mode = 3 -> output considering cities; mode = 3 -> output considering airlines
     * @return returns an unordered_set with the output's Airports, Countries, Cities or Airlines
     */
    std::unordered_set<std::string> bfsInNFlights(const std::string &source, int n, int mode);
    /**
     * @brief This function calls the listComponent function
     * @param source the source Airport's code
     * @param filter this optional argument will be ignored if the list is empty. In case it's not, only Flights using the Airlines inside the list will be considered
     * @return returns a vector of reachable Airport's codes from {source}
     */
    std::vector<std::string> reachableAirports(const std::string &source, std::list<Airline*> filter = {});
    /**
     * @brief This function calls the function bfsInNFlights with mode value 0
     * @param source the source Airport's code
     * @param n the maximum number of Flights
     * @return returns an unordered_set with the reachable Airports in n Flights
     */
    std::unordered_set<std::string> airportsInNFlights(const std::string &source, int n);
    /**
     * @brief This function calls the function bfsInNFlights with mode value 1
     * @param source the source Airport's code
     * @param n the maximum number of Flights
     * @return returns an unordered_set with the reachable Countries in n Flights
     */
    std::unordered_set<std::string> countriesInNFlights(const std::string &source, int n);
    /**
     * @brief This function calls the function bfsInNFlights with mode value 2
     * @param source the source Airport's code
     * @param n the maximum number of Flights
     * @return returns an unordered_set with the reachable Cities in n Flights
     */
    std::unordered_set<std::string> citiesInNFlights(const std::string &source, int n);
    /**
     * @brief This function calls the function bfsInNFlights with mode value 3
     * @param source the source Airport's code
     * @param n the maximum number of Flights
     * @return returns an unordered_set with the used Airlines in n Flights
     */
    std::unordered_set<std::string> airlinesInNFlights(const std::string &source, int n);
    /**
     * @brief This function calls the functions countFlights or dijkstra depending on mode value
     * @param source the source Airport's code
     * @param target the target Airport's code
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns the value of minimum flights from {source} to {target}, otherwise it calls dijkstra and returns the minimum distance from {source} to {target}
     */
    double minDistanceCodeCode(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a Coordinate and an Airport code
     * @param source source Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param target the target Airport's code
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCoordinateCode(Coordinate source, const std::string &target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a City's name and an Airport's code
     * @param source source City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param target the target Airport's code
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCityCode(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a Country's and an Airport's code
     * @param source source Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param target the target Airport's code
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCountryCode(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing an Airport's code and a Coordinate
     * @param source the source Airport's code
     * @param target target Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCodeCoordinate(const std::string &source, Coordinate target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing two Coordinates
     * @param source source Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param target target Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCoordinateCoordinate(Coordinate source, Coordinate target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a City's name and a Coordinate
     * @param source source City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param target target Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCityCoordinate(const std::string &source, Coordinate target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a Country's name and a Coordinate
     * @param source source Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param target target Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCountryCoordinate(const std::string &source, Coordinate target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing an Airport's code and a City's name
     * @param source the source Airport's code
     * @param target target City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCodeCity(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a Coordinate and a City's name
     * @param source source Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param target target City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCoordinateCity(Coordinate source, const std::string &target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing two City's names
     * @param source source City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param target target City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCityCity(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a Country's name and a City's name
     * @param source source Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param target target City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCountryCity(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing an Airport's code and a Country's name
     * @param source the source Airport's code
     * @param target target Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCodeCountry(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a Coordinate and a Country's name
     * @param source source Coordinate (the function will consider all Airport's Coordinates that dist less than {radius} from the input Coordinate and use the one that provides the minimum output}
     * @param target target Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @param radius the Airports considered will be {radius} km away from the input Coordinate
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCoordinateCountry(Coordinate source, const std::string &target, bool mode, double radius);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing a City's name and a Country's name
     * @param source source City (the function will consider all the City's airports and choose the one that provides the minimum output)
     * @param target target Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCityCountry(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calculates the minimum number of paths / minimum distance providing two Country's names
     * @param source source Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param target target Country (the function will consider all the Country's airports and choose the one that provides the minimum output)
     * @param mode defines which function to call
     * @return if mode == true calls countFlights and returns a pair of Airports {source,target} that generates a minimum number flights from {source} to {target}, otherwise it calls dijkstra and returns a pair of Airports {source,target} that generates the minimum distance from {source} to {target}
     */
    std::pair<Airport*,Airport*> minDistanceCountryCountry(const std::string &source, const std::string &target, bool mode);
    /**
     * @brief This function calls articulationAirports
     * @return returns a list with all the articulation Airports in the graph
     */
    std::list<Airport*> getArticulationAirports();
    /**
     * @brief This functions calls stronglyConnectedComponents for every unvisited Airport
     * @return returns a list of all the Strongly Connected Components of the graph
     */
    std::list<std::list<Airport*>> getStronglyConnectedComponents();
    /**
     * @brief This function calculates the diameter of the list provided in the first argument. If this argument is empty it provides the diameter of the entire graph
     * @param personalizedAirports this parameter allows a list of airports to be the target of this operation
     * @return returns the diameter of the intended component / of the entire graph
     */
    double getDiameter(std::list<Airport*> &personalizedAirports);
    /**
     * @brief This function can be used to extract the path made from an Airport {source} to an Airport {target}
     * @param source a pointer to the source Airport
     * @param target a pointer to the target Airport
     * @return returns a list with all the visited Airports from {source} to {target}
     */
    std::list<Airport*> path(Airport *source, Airport *target);

};

#endif //AED2223_G29_FLIGHTGRAPH_H
