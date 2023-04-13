import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.mplot3d.art3d import Poly3DCollection

if __name__ == "__main__":
    # read data with pandas and convert it to a numpy array
    df = pd.read_csv(r'/home/marco/Projekte/NelderMead/downhill_simplex.txt', sep=", ", engine='python')
    coordinate_array = df.to_numpy()
    length = coordinate_array.shape[0]

    # create a scatter plot for the himmelblau function to visualize the downhill simplex process
    fig, ax = plt.subplots(subplot_kw={"projection": "3d"}, figsize=(9, 9), dpi=160)
    ax.view_init(elev=60, azim=45, roll=0)
    x = np.arange(-6, 0, 0.05)
    y = np.arange(-6, 0, 0.05)
    x, y = np.meshgrid(x, y)
    f =  np.power((np.power(x, 2) + y - 11), 2) + np.power((x + np.power(y, 2) - 7), 2)
    surf = ax.scatter(x, y, f, c=f, alpha=0.14)

    def animate(i):
    '''
    Animation function
    '''
        x = coordinate_array[i, [0, 3, 6]]
        y = coordinate_array[i, [1, 4, 7]]
        f = np.power((np.power(x, 2) + y - 11), 2) + np.power((x + np.power(y, 2) - 7), 2)
        verts = [list(zip(x,y,f))]
        ax.add_collection3d(Poly3DCollection(verts, facecolors='grey', edgecolor="black", alpha=0.4))

    anim = animation.FuncAnimation(fig, animate, frames=length)
    writergif = animation.PillowWriter(fps=0.6) 
    anim.save("downhill_simplex.gif", writer=writergif)
