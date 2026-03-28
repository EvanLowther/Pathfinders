#%%
import pandas as pd
from cosmograph import cosmo
import os

# --- SETUP PATHS ---
base_path = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(base_path, '..', 'data', 'road_network.csv')

try:
    # --- DATA LOADING ---
    df = pd.read_csv(csv_path, dtype=int)  # Make sure node IDs are ints
    
    all_nodes = pd.concat([df['Source'], df['Target']]).unique()
    points = pd.DataFrame({'node_id': all_nodes})

    # --- NODE STATE & SIZE LOGIC ---
    path_nodes = ['10', '77', '76', '69','70','58','50']
    explored_nodes = ['10', '11', '22', '77', '44', '58', '69','76','197','45']

    def get_node_data(nid):
        nid_str = str(nid)
        if nid_str in path_nodes:
            return 'Path', 50000     # large size for visibility
        if nid_str in explored_nodes:
            return 'Explored', 50000
        return 'All Nodes', 0.1        

    points[['state', 'size']] = points['node_id'].apply(
        lambda x: pd.Series(get_node_data(x))
    )

    # --- LINK COLOR & WIDTH SYNC ---
    node_state_map = dict(zip(points['node_id'], points['state']))

    # Assign state to links based on source node
    df['link_state'] = df['Source'].map(node_state_map).fillna('All Nodes')

    # Map link state to color with opacity (RGBA)
    link_color_map = {
        'Path': 'rgba(41, 248, 4, 1.0)',       # green, fully opaque
        'Explored': 'rgba(239, 247, 6, 1.0)',  # yellow, fully opaque
        'All Nodes': 'rgba(255, 255, 255, 0.01)' # white, 20% opacity
    }
    df['link_color_custom'] = df['link_state'].map(link_color_map)

    # Uniform thickness for all links
    df['width'] = 0.2

    # --- NODE COLOR PALETTE ---
    my_palette = ["#EFF706", "#29F804", "#616460"]  # Explored, Path, All Nodes

    # --- INITIALIZE COSMOGRAPH WIDGET ---
    widget = cosmo(
        points=points,
        links=df,
        point_id_by='node_id',
        link_source_by='Source',
        link_target_by='Target',

        point_greyout_opacity=0.0,
        link_greyout_opacity=0.0,
        
        # Node Styling
        point_size_by='size', 
        point_color_by='state',
        point_color_palette=my_palette,
        
        # Link Styling
        link_color_by='link_color_custom',  # use the color column
        link_width_by='width',        
        
        background_color='#020617',
        fit_view_padding=0,  

        # --- SIMULATION DISABLED ---
        disable_simulation=True
    )

    # --- EXECUTION ---
    display(widget)

    print("-" * 30)
    print(f"Total Unique Nodes: {len(points):,}")
    print(f"Total Road Segments (Links): {len(df):,}")
    print("-" * 30)

except Exception as e:
    print(f"Error: {e}")
# %%