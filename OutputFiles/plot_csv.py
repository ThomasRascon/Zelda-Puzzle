import pandas as pd
from matplotlib import pyplot as plt
def plot_csv(csv_file_name,width,height,num_samples):
    xy=pd.concat([pd.DataFrame(pd.read_csv(csv_file_name,header=None)[0].apply(lambda tup:tup.split(' ')[0])).rename(columns={0:'x'}),
 pd.DataFrame(pd.read_csv(csv_file_name,header=None)[0].apply(lambda tup:tup.split(' ')[1])).rename(columns={0:'y'})],axis=1)
    x = xy['x'].astype(float)
    y = xy['y'].astype(float)
    plt.figure(figsize=(18, 8))
    plt.scatter(x, y, alpha=0.5)
    plt.title(f'{width}x{height} solution density vs. spatial density with {num_samples} samples')
    plt.xlabel('spatial density')
    plt.ylabel('solution density')
    plt.savefig(f'density_plot_{width}x{height}_with_{num_samples}_samples.png')