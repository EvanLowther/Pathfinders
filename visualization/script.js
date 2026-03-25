async function init() {
    const container = document.getElementById('graph-container');
    
    //Functionality/graphing the points (gets called in index.html)
    const CosmoClass = window.CosmoGraphClass;

    if (!CosmoClass) {
        //If it's not ready yet, wait 100ms and try again
        setTimeout(init, 100);
        return;
    }

    try {
        const response = await fetch('../data/road_network.json');
        const data = await response.json();

        //Cosmograph v2.2.1, using points and links to represent data
        const graph = new CosmoClass(container, {
            points: data.nodes,
            links: data.links,
            pointSize: 4,
            pointColor: '#4facfe',
            backgroundColor: '#0f172a',
            simulation: { repulsion: 0.1 }
        });

        console.log("Pennsylvania Road Network successfully initialized!");
        setTimeout(() => graph.zoomToNodes(data.nodes), 1000);

    } catch (err) {
        console.error("Initialization failed:", err);
    }
}

init();