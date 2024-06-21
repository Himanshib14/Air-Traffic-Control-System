<h1 id="air-traffic-control-system">Air Traffic Control System</h1>
<h2 id="introduction">Introduction</h2>
<p>This repository contains an implementation of an Air Traffic Control System for an operating systems (OS) assignment. The system simulates processes such as planes, airports, an air traffic controller, passengers, and cleanup using POSIX-compliant C programs.</p>
<h2 id="problem-statement">Problem Statement</h2>
<p>The assignment involves developing four POSIX-compliant C programs:</p>
<ul>
<li>
<p><strong>plane.c</strong>:</p>
<ul>
<li>Creates a plane process representing a new plane instance.</li>
<li>Collects user inputs for unique plane ID, type of plane (passenger or cargo), and relevant details.</li>
<li>Handles details like number of passengers, luggage weight, and body weight for passenger planes.</li>
<li>Manages details like number of cargo items and average weight for cargo planes.</li>
<li>Sends departure information to the air traffic controller upon readiness.</li>
</ul>
</li>
<li>
<p><strong>ATC.c</strong>:</p>
<ul>
<li>Manages plane arrivals, departures, and communications with airports.</li>
<li>Receives messages from planes and instructs airports accordingly via a single message queue.</li>
<li>Coordinates departure and landing processes.</li>
<li>Logs plane journeys in AirTrafficController.txt.</li>
</ul>
</li>
<li>
<p><strong>cleanup.c</strong>:</p>
<ul>
<li>Facilitates orderly termination of the entire system.</li>
<li>Upon user input (Y or N), requests termination from the air traffic controller via the message queue.</li>
</ul>
</li>
<li>
<p><strong>airport.c</strong>:</p>
<ul>
<li>Creates an airport process to handle plane arrivals and departures.</li>
<li>Sets up runways with load capacities and manages plane arrivals/departures.</li>
<li>Uses threading for handling simultaneous plane operations.</li>
<li>Interacts with the air traffic controller through the message queue.</li>
</ul>
</li>
</ul>
<h2 id="requirements">Requirements</h2>
<p>To run this project, ensure you have the following:</p>
<ul>
<li>Ubuntu 22.04 installed on your system.</li>
<li>GCC compiler for compiling C programs.</li>
<li>Terminal to execute commands.</li>
</ul>
<h2 id="installation-and-execution">Installation and Execution</h2>
<p>Follow these steps to run the project:</p>
<ol>
<li>
<p><strong>Clone the Repository:</strong></p>
<pre class=" language-bash"><code class="prism  language-bash"><span class="token function">git</span> clone https://github.com/Sarvaswa-Mohata/OS-Assignment-2
<span class="token function">cd</span> repository
</code></pre>
</li>
<li>
<p><strong>Compile the Programs:</strong></p>
<pre class=" language-bash"><code class="prism  language-bash">gcc plane.c -o plane
gcc ATC.c -o ATC
gcc cleanup.c -o cleanup
gcc airport.c -o airport
</code></pre>
</li>
<li>
<p><strong>Run the Programs:</strong></p>
<ul>
<li>
<p>Start the <strong>cleanup</strong> process:</p>
<pre class=" language-bash"><code class="prism  language-bash">./cleanup
</code></pre>
</li>
<li>
<p>Start the <strong>airtrafficcontroller</strong> process:</p>
<pre class=" language-bash"><code class="prism  language-bash">./ATC
</code></pre>
</li>
<li>
<p>Start multiple instances of the <strong>plane</strong> process:</p>
<pre class=" language-bash"><code class="prism  language-bash">./plane
</code></pre>
</li>
<li>
<p>Start multiple instances of the <strong>airport</strong> process:</p>
<pre class=" language-bash"><code class="prism  language-bash">./airport
</code></pre>
</li>
</ul>
</li>
</ol>
<h2 id="license">License</h2>
<p>This project is licensed under the <a href="https://opensource.org/licenses/MIT">MIT License</a>.</p>
<h2 id="conclusion">Conclusion</h2>
<p>This repository provides a comprehensive implementation of an Air Traffic Control System for the OS assignment. Follow the outlined steps to successfully compile and execute the program. Good luck!</p>

