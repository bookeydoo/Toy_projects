

function setup() {
    createCanvas(500, 500, WEBGL);
    
    }
  
  function draw() {
    background (200);
  
    fill(255,255,0);
    
    let bitesize=PI/8;
    let startangle=bitesize*sin(frameCount*0.05)+bitesize;
    let endangle=2*PI;
    arc(25,25,50,70,startangle,endangle,PIE);
  }