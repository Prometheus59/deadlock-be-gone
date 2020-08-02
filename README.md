#### CP386 - Assignment 4: Deadlock-Be-Gone
In this assignmnet we try to practice the concept of deadlock avoidance. 

#### Motivation: 
Assignment 4 for CP386 Spring 2020.
  
#### Installation:
To install, please clone the repository and save it locally. You should have a zip folder that incldues everything you need. Unzip this folder before you try to run anything. 

In your terminal, navigate to the root directory previously unzipped folder.

Run the MAKE command by typing `make` in your terminal.

Run the program by typing `./test` followed by your resources, for example `./test 10 5 7 8`

#### Screenshots:
![Request](/images/request.png)

![Release](/images/release.png)

![Run1](/images/run1.png)
![Run2](/images/run2.png)

![*](/images/star.png)

#### Contribution:
* <pre>main:             Ryan Karumanchery & Ramandeep Saini</pre>
* <pre>read_file:        Ramandeep Saini</pre>
* <pre>request_res:      Ryan Karumanchery</pre>
* <pre>release_res:      Ryan Karumanchery & Ramandeep Saini</pre>
* <pre>run:              Ryan Karumanchery</pre>
* <pre>output_data:      Ryan Karumanchery</pre>
* <pre>run_thread:       Ryan Karumanchery</pre>
* <pre>safety_algorithm: Ryan Karumanchery</pre>

#### Features:
* <pre>main:             Initalize variables and contains main function loop.</pre>     
* <pre>read_file:        Reads text file into the 2D matrix maximum.</pre>        
* <pre>request_res:      Request resources.</pre>        
* <pre>release_res:      Release resources.</pre>
* <pre>run:              Runs all threads.</pre>     
* <pre>output_data:      Outputs available resources, maximum resources, allocation, and resources needed.</pre>
* <pre>run_thread:       Runs a thread.</pre>
* <pre>safety_algorithm: Algorithm to determine if state is safe.</pre>

#### Tests:
Please see screenshots.
Two files used for testing data are avaible in the installed folder.

#### Code Example:
Command for requesting resources.
<pre>Enter Command: RQ 0 3 1 2 1</pre>

Command for releasing resources.
<pre>Enter Command: RL 0 1 1 1 1</pre>

Command for running threads.
<pre>Enter Command: Run</pre>

Command for outputting available resources, maximum 
resources, allocation, and resources needed.
<pre>Enter Command: *</pre>

#### Authors:
* Ryan Karumanchery
* Ramandeep Saini