import matplotlib.pyplot as plt
import numpy as np

# Open the output.txt file.
with open('output.txt') as file:
    # Import the data.
    lines = file.readlines()
    # Separate the data into numpy arrays.
    single_vector = np.fromstring(lines[0], dtype=float, sep=',')
    double_vector = np.fromstring(lines[1], dtype=float, sep=',')
    extended_vector = np.fromstring(lines[2], dtype=float, sep=',')

# Change the font settings and use LaTeX as the text renderer.
plt.rc('text', usetex=True)
plt.rc('font', **{'family': 'sans-serif', 'sans-serif': ['cm']})
plt.rc('text.latex', preamble=r'\usepackage{sfmath}')


def plot_fig(accuracy_vector, theory_val):
    """
    Plots a graph of accuracy upper bound against algorithm step. Includes a
    line showing the theoretical value.

    Arguments:
         - accuracy_vector: An array of accuracy upper bounds in the order to
                            be plotted.

    Returns:
         - A figure object representing the graph.
    """

    # Initialise the figure and set the size.
    fig = plt.figure(figsize=(6, 6))

    # Plot the data.
    plt.plot(np.arange(1, accuracy_vector.size + 1), accuracy_vector, '-bx')

    # Add an additional line
    plt.plot(np.arange(1, accuracy_vector.size + 1),
             np.ones(accuracy_vector.size) * theory_val,
             'r--')

    # Formatting suitable for insertion in the report.
    plt.grid()
    plt.xlabel("Algorithm Step", fontsize=16)
    plt.ylabel("Upper Bound on Machine Accuracy", fontsize=16)

    return fig


# Plot accuracy upper bound against step for single precision floats.
# Uses the theoretical value of 2^-24 [IEEE Std 754-2008].
fig1 = plot_fig(single_vector, 2.0**-24)
# Save the figure.
fig1.savefig("single_accuracy.png")

# Plot accuracy upper bound against step for double precision floats.
# Uses the theoretical value of 2^-53 [IEEE Std 754-2008].
fig2 = plot_fig(double_vector, 2.0**-53)
# Save the figure.
fig2.savefig("double_accuracy.png")

# Plot accuracy upper bound against step for extended precision floats.
# Uses the theoretical value of 2^-64 [GCC Documentation 2017].
fig2 = plot_fig(extended_vector, 2.0**-64)
# Save the figure.
fig2.savefig("extended_accuracy.png")

# Display the figure.
plt.show()
