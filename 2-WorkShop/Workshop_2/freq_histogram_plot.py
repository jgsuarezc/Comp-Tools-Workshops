import pandas as pd 
import matplotlib.pyplot as plt 
import numpy as np

df_histogam = pd.read_csv("freq_histogram.csv", names = ["xmin","xmax","nbins","sample"])

freq = df_histogam["sample"].to_list()
xmin = df_histogam["xmin"].to_list()[0]
xmax = df_histogam["xmax"].to_list()[0]
nbins = df_histogam["nbins"].to_list()[0]

bins = [x for x in np.linspace(xmin,xmax,nbins)]
plt.plot(bins, freq)
plt.savefig("freq_histogram.pdf")

