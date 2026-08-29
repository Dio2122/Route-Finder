# Klang Valley Transit Route - Shortest Path Finder

A C++ Data Structures & Algorithms project that models a transit network (LRT Kelana Jaya Line & Sunway BRT Line interchange) as a weighted graph using custom adjacency linked lists, calculating the shortest transit routes and distances via **Dijkstra's Algorithm**.

---

## Features

- **Custom Graph Representation:** Models stations and bidirectional routes using linked-list-based adjacency structures (`Station` and `Route` structs).
- **Dijkstra's Shortest Path Algorithm:** Computes the minimal travel distance between any two transit stations across the network.
- **Path Reconstruction:** Backtracks and renders the full sequential route (station-by-station) from origin to destination.
- **Input Validation & Safety:** Robust terminal input checking and loop protections against invalid selections or identical source-destination inputs.

---

## Stations & Network

The graph covers 12 major transit stops across Subang Jaya and Bandar Sunway:
- **LRT Stations:** SS15, SS18, USJ 7 (Interchange), Taipan, Wawasan, USJ 21
- **BRT Stations:** South Quay - USJ 1, SunU - Monash, SunMed, Sunway Lagoon, Mentari, Sunway - Setia Jaya

---

## Getting Started

### Prerequisites

- A standard C++ compiler (`g++`, `clang++`, or MSVC) supporting **C++11** or newer.

### Compilation

Compile the source code:

```bash
g++ -std=c++11 main.cpp -o transit_route_finder