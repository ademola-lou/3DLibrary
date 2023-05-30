import { ArcRotateCamera } from "@babylonjs/core/Cameras/arcRotateCamera";
import { Engine } from "@babylonjs/core/Engines/engine";
import { HemisphericLight } from "@babylonjs/core/Lights/hemisphericLight";
import { Vector3 } from "@babylonjs/core/Maths/math.vector";
import { Scene } from "@babylonjs/core/scene";

export function renderScene(): Promise<any> {
    const canvas = document.getElementById("app") as HTMLCanvasElement;
    const engine = new Engine(canvas);
    const scene = new Scene(engine);

    function renderLoop(){
     scene.render();
    }
    engine.runRenderLoop(renderLoop);
    
    const camera = new ArcRotateCamera("Camera", 0, 0.8, 100, Vector3.Zero(), scene);
    camera.attachControl(canvas, false);
    camera.setPosition(new Vector3(0, 5, -10))
    
    const light = new HemisphericLight("light", new Vector3(0, 1, 0), scene);
    
    // Default intensity is 1. Let's dim the light a small amount
    light.intensity = 0.7;

    window.addEventListener("resize", () => {
        engine.resize();
    });

    return new Promise((resolve) => {
        scene.whenReadyAsync().then(() => {
            resolve(scene);
        
        })
    })
    
}
