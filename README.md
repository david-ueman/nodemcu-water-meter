# nodemcu-water-meter

# About

The NodeMCU Water Meter it's a volume meter specifically though to measure and report the amount of liquid stored in the water deposits that are used to capture the rain water in isolated installations without access to water, like the squatt ESLA EKO (eslaeko.net) in Madrid.

For this project, the NodeMCU has an ultrasonic sensor attached to it that sends a sonic signal to the water. The signal is emitted and bounced back to the sensor. Depending on the time that it takes to go and come back we can know the distance. By knowing the distance between the sensor and the water we can also know the amount of liquid stored in the deposits.

This information is then sent to a web server where is stored and made public by some other scripts written in PHP.
