# ElectricFence
Arduino project to emulate and electric fence transmitter

#Explanation
First, the output of an electric fence product was captured in Digilent Waveforms using a Digilent Analog Discovery 2 board. The capture was made at 800k samples per second, for a second. This capture was omitted in this repository due to its size.

Next, this was converted from a CSV to a raw format for usage in GNU Radio Companion. Timestamps were removed using a simple regex in a text editor (vim). Then, analysis/convert.cpp was written to take in the list of decimal numbers and return a file of raw (4 byte) floats.

This was imported into analysis/differentiate.grc, which plotted the signal for analysis, and output another raw file with the absolute value of the derivative of the signal.

Next, this differentiated signal and the raw original signal were read by analysis/analyze.cpp, which scanned both. When it encountered a derivative which exceeded a threshold (max amplitude was 1, .3 was selected empircally), it looked 5 samples (again empirically selected) ahead in the original waveform and set the output to be either -1, 0, or 1 based on that value. It would also skip close occurrences of high derivatives, to avoid redundancy. This program output a raw file with the reconstructed waveform, and a CSV containing the times when a signal changed value, and what value it changed to.

Finally, each column in this CSV was converted into a C array, again using regexes (in vim). These arrays are the meat behind the Arduino code (found in data.h), which just iterates through them and changes its output to the specified value when appropriate.

Throughout this process, the various stages of raw output were imported into Audacity (File->Import->Raw Data-> (32-bit float, Little-endian, 1 Channel (Mono)) for visualization, to ensure that the signals looked as expected.
