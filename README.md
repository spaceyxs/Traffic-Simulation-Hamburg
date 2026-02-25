# Traffic-Simulation-Hamburg
## Project Overview
This project models and simulates urban traffic congestion on a specific street in Hamburg, Germany. Developed using the Discrete Event System Specification (DEVS) formalism and the Cadmium simulation framework, the project analyzes how vehicles arrive, move, and interact with traffic control systems during rush hour.

The objective is to monitor vehicle accumulation and queue formation based on real-world traffic volume metrics.

## Model Architecture
The system consists of four primary atomic models integrated into a two hierarchical coupled structure.
### Atomic Models
**Car Generator**: Creates vehicle objects using an exponential distribution to model independent arrival times.

**Road Segment**: Represents a section of the road; it maintains a vehicle queue and simulates travel time.

**Traffic Light**: A state-based controller that cycles through specific color phases and durations.

**Intersection**: Controls vehicle passage based on the current traffic light color received.

### Coupled Models
**Intersection Coupled**: Integrates the Road Segment, Traffic Light, and Intersection atomic models.

**Top Coupled**: The top-level model connecting the Car Generator to the Intersection Coupled subsystem.

---

## Traffic Light Phase and Color Specifications
The Traffic Light atomic model is configured with a specific sequence and timing to control the flow of traffic at the intersection:

**Green Phase**: Duration of 7 seconds, allowing vehicles to pass through the intersection.

**Yellow Phase**: Duration of 2 seconds, serving as a transition state

**Red Phase**: Duration of 5 seconds, stopping all vehicle flow to simulate cross-traffic or pedestrian interval.

The state transitions follow the continuous sequence: **GREEN → YELLOW → RED → GREEN**. The Intersection model only allows vehicle movement during the **GREEN** or **YELLOW** light states.

---

## Data Foundation and Methodology
The simulation is grounded in data obtained from the official Hamburg open data portal.

### Configuration via DTVw
The model uses Average Daily Weekday Traffic (DTVw) to set traffic intensity. To simulate rush hour, the project assumes that 10% of total daily traffic occurs during the peak hour.

The vehicle arrival rate ($\lambda$) is calculated as follows:

$$\lambda = \frac{0.10 \times DTVw}{3600}$$

---

## Simulation Results
The project evaluated two scenarios to determine the effect of traffic volume on congestion:

| Metric | Scenario 1 (High Volume) | Scenario 2 (Low Volume) |
| :--- | :--- | :--- |
| **DTVw Value** | 33,000  | 16,000 |
| **Max Queue Size** | 12 vehicles  | 6 vehicles  |
| **Generation Count** | 21 vehicles by t = 18.61s  |12 vehicles by t = 19.95s  |

**Conclusion**: Higher DTVw values result in higher vehicle arrival rates, leading to increased queue sizes and higher system load.

---

## Technical Specifications

**Framework**: Cadmium DEVS

**Language**: C++ 

**Data Source**: [Transparenzportal Hamburg](https://suche.transparenz.hamburg.de/dataset/verkehrsmengen-auf-hauptverkehrsstrassen-in-hamburg45) 

