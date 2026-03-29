#%%
import pandas as pd
from cosmograph import cosmo
import os

# --- SETUP PATHS ---
base_path = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(base_path, '..', 'data', 'road_network.csv')
astar_path_csv = os.path.join(base_path, '..', 'output', 'astar_path.csv')
astar_explored_csv = os.path.join(base_path, '..', 'output', 'astar_explored.csv')
dijkstra_path_csv = os.path.join(base_path, '..', 'output', 'dijkstra_path.csv')
dijkstra_explored_csv = os.path.join(base_path, '..', 'output', 'dijkstra_explored.csv')

try:
    # --- DATA LOADING ---
    df_road = pd.read_csv(csv_path, dtype=int)
    all_nodes = pd.concat([df_road['Source'], df_road['Target']]).unique()
    points = pd.DataFrame({'node_id': all_nodes})

    # --- USER CHOICE ---
    choice = input("Which algorithm to display? \n1.A* \n2.Dijkstra").strip().lower()
    if choice == '1':
        path_csv = astar_path_csv
        explored_csv = astar_explored_csv
    elif choice == '2':
        path_csv = dijkstra_path_csv
        explored_csv = dijkstra_explored_csv
    else:
        print("Invalid choice, defaulting to A*")
        path_csv = astar_path_csv
        explored_csv = astar_explored_csv

    # --- NODE STATE & SIZE LOGIC ---
    path_nodes = pd.read_csv(path_csv, dtype=int)['node_id'].astype(str).tolist()
    explored_nodes = pd.read_csv(explored_csv, dtype=int)['node_id'].astype(str).tolist()

    # Identify start and end nodes
    if path_nodes:
        start_node = path_nodes[0]
        end_node = path_nodes[-1]
    else:
        start_node = end_node = None

    def get_node_data(nid):
        nid_str = str(nid)
        if nid_str == start_node or nid_str == end_node:
            return 'Shortest_Path', 100       # extra large for visibility
        if nid_str in path_nodes:
            return 'Shortest_Path', 20
        if nid_str in explored_nodes:
            return 'Explored', 5
        return 'All Nodes', 1        

    points[['state', 'size']] = points['node_id'].apply(lambda x: pd.Series(get_node_data(x)))

    # --- LINK COLOR & WIDTH SYNC ---
    node_state_map = dict(zip(points['node_id'], points['state']))
    df = df_road.copy()
    df['link_state'] = df['Source'].map(node_state_map).fillna('All Nodes')

    link_color_map = {
        'Shortest_Path': 'rgba(0, 33, 165, 1.0)',
        'Explored': 'rgba(250, 70, 22, 0.01)',
        'All Nodes': 'rgba(255, 255, 255, 0.01)'
    }
    df['link_color_custom'] = df['link_state'].map(link_color_map)
    df['width'] = 0.2

    # --- NODE COLOR PALETTE ---
    my_palette = ["#0021A5", "#FA6A16A9", "#616460"]  # Explored, Path, All Nodes

    # --- INITIALIZE COSMOGRAPH WIDGET ---
    widget = cosmo(
        points=points,
        links=df,
        point_id_by='node_id',
        link_source_by='Source',
        link_target_by='Target',

        point_greyout_opacity=0.0,
        link_greyout_opacity=0.0,
        
        point_size_by='size',
        point_size_range=[1, 100],  # min/max size scaling based on zoom
        point_color_by='state',
        point_color_palette=my_palette,
        
        link_color_by='link_color_custom',
        link_width_by='width',
        
        background_color='#020617',
        fit_view_padding=0,  

        disable_simulation=False
    )

    # --- DISPLAY ---
    display(widget)
    print("-" * 30)
    print(f"Total Unique Nodes: {len(points):,}")
    print(f"Total Road Segments (Links): {len(df):,}")
    print("-" * 30)

except Exception as e:
    print(f"Error: {e}")

# %%