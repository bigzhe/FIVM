import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
import matplotlib.patches as patches

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
df['query_root'] = df['query_root'].str.strip()

# Directory to save plots
output_dir = 'viz'
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Loop through unique names
for unique_name in df['name'].unique():
    # Filter the data for the current name
    name_data = df[df['name'] == unique_name]

    # Unique query roots
    query_roots = name_data['query_root'].unique()

    # Unique executors
    executors = name_data['executor'].unique()
    # Define colors for executors
    color_map = {executor: color for executor, color in zip(executors, ['blue', 'orange'])}

    # Width of a bar
    bar_width = 0.35

    fig, ax = plt.subplots()

    bar_distance = 0.05
    # Start position for the first bar
    start_pos = 0
    # Keep track of x-ticks positions
    x_ticks = []

    # Loop through query roots
    for qr_idx, query_root in enumerate(sorted(query_roots)):
        # Number of queries within the current query root
        start = start_pos
        # Loop through executors
        for ex_idx, executor in enumerate(executors):
            version_data = name_data[(name_data['query_root'] == query_root) & (name_data['executor'] == executor)]['dataset'].unique()
            length = len(name_data[(name_data['query_root'] == query_root) & (name_data['executor'] == executor)])/len(version_data)
            positions = start_pos + np.arange(length) * (bar_width + bar_distance)
            first = True
            for version in version_data:
                query_data = name_data[(name_data['query_root'] == query_root) & (name_data['executor'] == executor) & (name_data['dataset'] == version)]
                heights = query_data['update_time'].values

                # Positions calculation

                # Plot bars for each query within a query_root
                bars = ax.bar(positions, heights, width=bar_width, color=color_map[executor], alpha=0.6)
                if first:
                    first = False
                    for bar, label in zip(bars, query_data['query']):
                        height = bar.get_height()
                        ax.text(bar.get_x() + bar.get_width() / 2, height, label,
                                ha='center', va='bottom', rotation=90, fontsize=8)

            # Updating the start position for the next executor
            start_pos = positions[-1] + bar_width + bar_distance

        x_ticks.append((start_pos + start) / 2 - bar_width / 2 - bar_distance / 2)
        # Updating the start position for the next query root group and storing x-ticks
        start_pos += bar_width * 2

    legend_handles = []
    for ex_idx, executor in enumerate(executors):
        version_data = name_data[name_data['executor'] == executor]['dataset'].unique()
        color = color_map[executor]
        n_versions = len(version_data)
        for version_idx, version in enumerate(version_data):
            # manually adjust alpha to simulate lightening effect
            alpha = 1 - version_idx * 0.3
            alpha = max(0.3, alpha)  # Keep alpha above 0.3 to avoid too much transparency
            patch = patches.Patch(color=color, alpha=alpha, label=f'{executor} - {version}')
            legend_handles.append(patch)

    # Set x-ticks to the middle of each query root group
    ax.set_xticks(x_ticks)
    ax.set_xticklabels(sorted(query_roots))

    ax.set_xlabel('Query Root')
    ax.set_ylabel('Update Time (ms)')
    ax.legend(handles=legend_handles, loc='upper left', bbox_to_anchor=(1, 1), title="Executor - Version")

    # Save plot
    plt.savefig(os.path.join(output_dir, f'{unique_name}_plot.png'), bbox_inches='tight')
    plt.close()