import { CosmoGraph } from 'https://cdn.skypack.dev/@cosmograph/cosmograph';


const container = document.getElementById('graph-container');
const status = document.getElementById('status');

async function init() {
    try {
        status.innerText = "Fetching JSON data...";
        const response = await fetch('../data/road_network.json');
        if (!response.ok) throw new Error("Could not find road_network.json in /data");

        const data = await response.json();
        status.innerText = `Loaded ${data.nodes.length} nodes. Calculating layout...`;

        const config = {
            nodes: data.nodes,
            links: data.links,
            nodeSize: 2,
            nodeColor: '#4facfe',
            linkWidth: 0.1,
            linkColor: '#ffffff33',
            backgroundColor: '#0f172a',
            simulation: {
                repulsion: 0.5,
                gravity: 0.1,
                friction: 0.5,
                linkDistance: 15,
                linkStrength: 1
            }
        };

        const graph = new CosmoGraph(container, config);
        
        setTimeout(() => {
            graph.zoomToNodes(data.nodes);
            status.innerText = "Visualization Ready.";
        }, 1000);

    } catch (err) {
        status.innerText = "Error!";
        console.error(err);
    }
}

init();