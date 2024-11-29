import p5 from 'p5';

new p5((p) => {
  p.setup = () => {
    p.createCanvas(500, 500, p.WEBGL);
  };

  p.draw = () => {
    p.background(200);
    p.fill(255, 255, 0);
    let bitesize = p.PI / 8;
    let startangle = bitesize * p.sin(p.frameCount * 0.05) + bitesize;
    let endangle = 2 * p.PI;
    p.arc(25, 25, 50, 70, startangle, endangle, p.PIE);
  };
});
