# Masters disseratation project (UoB)


The project is primarily written in C++, and Python was used to plot 


To run the GA:
```
export FILE=main
make <rule>
```

To evaluate the GA, run the experiments file with:
```
export FILE=experiment
make <rule>
```

where _rule_ can be 'default', 'diagnostic', 'debug' or 'speedy'.

The main and experiment file generate data that is stored in  "data/".

To plot the data, run the python script with:
```
python plotter.py
```
The plots are saved to the "plots/" folder.

