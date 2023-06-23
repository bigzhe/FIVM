import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
import matplotlib.patches as patches
import matplotlib.colors as mcolors

# Read the text file
with open('output/output.txt', 'r') as f:
    lines = f.readlines()

# Parse the data
data = []
for line in lines:
    name_dataset_processing, *rest = line.strip().split(':')
    name, executor, dataset, _, all_relations = name_dataset_processing.split('|')
    base = [name, dataset, all_relations]
    for res in rest:
        subname, maptype, update_time, enumeration_time, count, varnames, relations = res.split('|')

        data.append(
            base + [executor, subname, maptype, int(update_time), int(enumeration_time), int(count), varnames, relations])

# Create a DataFrame
df = pd.DataFrame(data)
df.columns = ['name', 'dataset', 'all Relations', 'executor', 'query', 'maptype', 'update_time', 'enumeration time',
              'nr tuples', 'free variables', 'relations']

# Extract root query name
df['query_root'] = df['query'].str.extract(r'(\D*\d+)')
df['query_unique_root'] = df['query_root'].str.strip() + ' - ' + df['free variables'].str.strip()

# Directory to save plots
output_dir = 'viz'
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Loop through unique names
for unique_name in df['name'].unique():
    # Filter the data for the current name
    name_data = df[df['name'] == unique_name]

    # Unique query roots
    query_roots = name_data['query_unique_root'].unique()

    # Unique executors
    executors = name_data['executor'].unique()

    # Colors for executors
    base_colors = ['blue', 'orange']

    # Width of a bar
    bar_width = 0.35

    fig, axes = plt.subplots(1, 2, figsize=(12, 6), sharey=True)

    bar_distance = 0.05
    for idx, metric in enumerate(['update_time', 'enumeration time']):
        ax = axes[idx]

        # Start position for the first bar
        start_pos = 0
        # Keep track of x-ticks positions
        x_ticks = []

        combination_legend_handles = []
        handled_combinations = set()  # To keep track of handled combinations

        # Loop through query roots
        for qr_idx, query_root in enumerate(sorted(query_roots)):
            # Number of queries within the current query root
            start = start_pos
            # Loop through executors
            for ex_idx, executor in enumerate(executors):
                version_data = name_data[(name_data['query_unique_root'] == query_root) & (name_data['executor'] == executor)]['dataset'].unique()
                if len(version_data) == 0:
                    continue
                length = len(name_data[(name_data['query_unique_root'] == query_root) & (name_data['executor'] == executor)]) / len(version_data)
                positions = start_pos + np.arange(length) * (bar_width + bar_distance)
                first = True
                base_color = mcolors.hex2color(base_colors[ex_idx])
                base_hsv = mcolors.rgb_to_hsv(base_color)
                for version_idx, version in enumerate(version_data):
                    shade = base_hsv.copy()
                    shade[2] = max(0.1, shade[2] - version_idx * 0.4)
                    color = mcolors.hsv_to_rgb(shade)
                    group = name_data[(name_data['query_unique_root'] == query_root) & (name_data['executor'] == executor) & (name_data['dataset'] == version)]

                    # Calculate the average and standard deviation for the group
                    avg_height = group[metric].mean() / 1000
                    std_height = group[metric].std() / 1000
                    position = start_pos + (bar_width + bar_distance) * version_idx

                    # Plot bars with error bars
                    bar = ax.bar(position, avg_height, width=bar_width, color=color, alpha=1, yerr=std_height)
                    if first:
                        first = False
                        name = name_data[(name_data['query_unique_root'] == query_root)].iloc[0]['query']
                        ax.text(bar[0].get_x() + bar[0].get_width() / 2, avg_height, name,
                                ha='center', va='bottom', rotation=90, fontsize=8)


                    # Add patch for legend if combination is not handled
                    combination = f'{executor} - {version}'
                    if combination not in handled_combinations:
                        combination_patch = patches.Patch(color=color, label=combination)
                        combination_legend_handles.append(combination_patch)
                        handled_combinations.add(combination)

                # Updating the start position for the next executor
                start_pos = positions[-1] + bar_width + bar_distance

            x_ticks.append((start_pos + start) / 2 - bar_width / 2 - bar_distance / 2)
            # Updating the start position for the next query root group and storing x-ticks
            start_pos += bar_width * 2

        # Set x-ticks to the middle of each query root group
        ax.set_xticks(x_ticks)
        ax.set_xticklabels(sorted(query_roots))

        ax.set_xlabel('Query')
        ax.set_ylabel(f'{metric.replace("_", " ").capitalize()} (s)')

        # Add legend to the first plot only
        if idx == 1:
            ax.legend(handles=combination_legend_handles, loc='upper right', bbox_to_anchor=(1, 1), title="Executor - Version")

    # Save plot
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    fig.suptitle(unique_name)
    plt.savefig(os.path.join(output_dir, f'{unique_name}_plot.png'), bbox_inches='tight', dpi=300)
    plt.close()