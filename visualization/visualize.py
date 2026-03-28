#%%
import pandas as pd
from cosmograph import cosmo
import os


# --- SETUP PATHS ---
base_path = os.path.dirname(os.path.abspath(__file__))
csv_path = os.path.join(base_path, '..', 'data', 'road_network.csv')

try:
    # --- DATA LOADING ---
    df = pd.read_csv(csv_path)
    
    all_nodes = pd.concat([df['Source'], df['Target']]).unique()
    points = pd.DataFrame({'node_id': all_nodes})

    # --- NODE STATE & SIZE LOGIC ---
    # Example IDs for testing
    path_nodes = ['0', '1', '6353', '4014', '2476']
    explored_nodes = ['0', '1', '6353', '4014', '4455', '2475', '2476']

    def get_node_data(nid):
        nid_str = str(nid)
        #Path first so it overrides Explored
        if nid_str in path_nodes:
            return '1_path', 20      
        #Check Explored
        if nid_str in explored_nodes:
            return '0_explored', 15  
        #Unexplored
        return '2_default', 1        

    points[['state', 'size']] = points['node_id'].apply(
        lambda x: pd.Series(get_node_data(x))
    )

    # --- LINK COLOR & WIDTH SYNC ---
    node_state_map = dict(zip(points['node_id'], points['state']))
    df['link_state'] = df['Source'].map(node_state_map).fillna('2_default')

    #Thickness logic based on node type
    def get_link_width(state):
        if state == '1_path': return 0.3      
        if state == '0_explored': return 0.3 
        return 0.1                            

    df['width'] = df['link_state'].apply(get_link_width)

    #Color Pallete for path, explored, and unexplored
    my_palette = ["#EFF706", "#29F804", "#616460"]

    # --- INITIALIZE COSMOGRAPH WIDGET ---
    widget = cosmo(
        points=points,
        links=df,
        point_id_by='node_id',
        link_source_by='Source',
        link_target_by='Target',

        point_greyout_opacity=0.0,   #Makes unselected nodes disappear
        link_greyout_opacity=0.0,   #Makes unselected links disappear
        
        # Node Styling
        point_size_by='size', 
        point_color_by='state',
        point_color_palette=my_palette,
        
        # Link Styling
        link_color_by='link_state',
        link_width_by='width',        
        
        background_color='#020617',
        fit_view_padding=0,  

        # --- SIMULATION ---
        disable_simulation=False,
        simulation_gravity=0.15,      
        simulation_repulsion=0.4,     
        simulation_friction=0.7,      
        simulation_link_spring=1.0,   
        simulation_link_distance=2    
    )

    # --- EXECUTION ---
    display(widget)   # works in Jupyter

    print("-" * 30)
    print(f"Total Unique Nodes: {len(points):,}")
    print(f"Total Road Segments (Links): {len(df):,}")
    print("-" * 30)

except Exception as e:
    print(f"Error: {e}")
# %%