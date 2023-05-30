import './style.css'
// import {Module} from './createWasmModule';
import { renderScene } from './renderView';
import { objPars, readFile } from './utils/parseObj';
import { createMesh, updateMesh } from './utils/MeshBufferUtils';
import { CGALWrapper, Smooth_Algorithm } from './createWasmModule';
import { Color3, Color4 } from '@babylonjs/core/Maths/math.color';
import { Vector3 } from '@babylonjs/core/Maths/math.vector';
import { CreateLineSystem } from '@babylonjs/core/Meshes/Builders/linesBuilder';
import { CreateBox } from '@babylonjs/core/Meshes/Builders/boxBuilder';
import { VertexBuffer } from '@babylonjs/core/Buffers/buffer';
import { SceneLoader } from '@babylonjs/core';
import "@babylonjs/loaders/OBJ"
import { AdvancedDynamicTexture } from '@babylonjs/gui/2D/advancedDynamicTexture';
import { StackPanel } from '@babylonjs/gui/2D/controls/stackPanel';
import { Button } from '@babylonjs/gui/2D/controls/button';
import { Control } from '@babylonjs/gui';

renderScene().then(scene => {

  const url = "../public/assets/suzanne.obj"
    //"https://rawcdn.githack.com/rezaali/webgl-sketches/master/models/bigguy.obj"
  //"../public/assets/hand_model.obj"
  // "../public/assets/monkey_tri.obj"
  // "../public/assets/segment_test.obj"
  //"../public/assets/suzanne.obj"
  //"/assets/suzanne.obj"
  //"https://rawcdn.githack.com/rezaali/webgl-sketches/master/models/bigguy.obj"
  //"https://cdn.glitch.me/b6638abd-afc2-4530-bc1b-8edf2eccdaad/box.obj?v=1639938146405";
  //"https://rawcdn.githack.com/rezaali/webgl-sketches/master/models/venus.obj";

  // "https://rawcdn.githack.com/rezaali/webgl-sketches/master/models/bigguy.obj"
  /*SceneLoader.ImportMeshAsync("", "", url, scene).then(result =>{
    console.log(result)
    result.meshes.forEach(mesh => {
      if(mesh.getTotalVertices() > 0){
        let positions = (mesh.getVerticesData(VertexBuffer.PositionKind) as any);
        let indices = Array.from(mesh.getIndices() as any);

        let cells0: any[] = []
        for(let i = 0; i < indices.length; i+=3){
          cells0.push([indices[i], indices[i+1], indices[i+2]] as any);
        }

        CGALWrapper.init();
        CGALWrapper.populateMesh({positions: positions, indices: cells0});
        CGALWrapper.smoothMesh(Smooth_Algorithm.Catmull_Clark);
        const mesh_data = CGALWrapper.getMeshData() as any;
        updateMesh(mesh as any, {...mesh_data, colors: null});

        readFile(url, (data: string) => {
          const result = objPars(data, null);
          let { positions, cells } = result;
          console.log("diff", cells, cells0)
        })
      }
    })
  })*/
  
  readFile(url, (data: string) => {
    const result = objPars(data, null);
    let { positions, cells } = result;
    positions = positions.flat();

    CGALWrapper.init();
    CGALWrapper.populateMesh({positions: positions, indices: cells});
    let {positions: newPositions, indices: newIndices} = CGALWrapper.getMeshData();
    const mesh = createMesh(scene, {positions: newPositions, indices: newIndices });
    mesh.normalizeToUnitCube();
    mesh.scaling.scaleInPlace(5);
    
    
    //create wireframe
    const myLines = [];
    for(var n = 0; n<cells.length; n++){
      var wirefaces = []
      for(var j = 0; j<cells[n].length; j++){
      var ind = cells[n][j]
      const wireframePoints = new Vector3(positions[(ind * 3) % positions.length], positions[(ind * 3 + 1) % positions.length], positions[(ind * 3 + 2) % positions.length])
      wirefaces.push(wireframePoints)

      }
      wirefaces.push(wirefaces[0])
      myLines.push(wirefaces)
    }

    const wireframe = CreateLineSystem("wireframe", {lines: myLines}, scene);
    wireframe.color = Color3.Green();
    wireframe.normalizeToUnitCube();
    wireframe.scaling.scaleInPlace(5);
    wireframe.rotation.y = Math.PI;



    const advancedTexture = AdvancedDynamicTexture.CreateFullscreenUI("UI");
    const stackPanel = new StackPanel();
    stackPanel.background = "green";
    stackPanel.width = "220px";
    stackPanel.horizontalAlignment = Control.HORIZONTAL_ALIGNMENT_RIGHT;
    advancedTexture.addControl(stackPanel);

    let clarkMulBt = Button.CreateSimpleButton("but1", "Catmull-Clark");
    clarkMulBt.height = "40px";
    clarkMulBt.onPointerUpObservable.add(function() {
      CGALWrapper.smoothMesh(Smooth_Algorithm.Catmull_Clark);
      const mesh_data = CGALWrapper.getMeshData() as any;
      updateMesh(mesh, {...mesh_data, colors: null});
    });
    stackPanel.addControl(clarkMulBt);

    let loopBt = Button.CreateSimpleButton("but2", "Loop");
    loopBt.height = "40px";
    loopBt.onPointerUpObservable.add(function() {
      CGALWrapper.smoothMesh(Smooth_Algorithm.Loop);
      const mesh_data = CGALWrapper.getMeshData() as any;
      updateMesh(mesh, {...mesh_data, colors: null});
    });
    stackPanel.addControl(loopBt);

    let dooSabinBt = Button.CreateSimpleButton("but3", "Doo-Sabin");
    dooSabinBt.height = "40px";
    dooSabinBt.onPointerUpObservable.add(function() {
      CGALWrapper.smoothMesh(Smooth_Algorithm.Doo_Sabin);
      const mesh_data = CGALWrapper.getMeshData() as any;
      updateMesh(mesh, {...mesh_data, colors: null});
    });
    stackPanel.addControl(dooSabinBt);

    let sqrtBt = Button.CreateSimpleButton("but4", "Sqrt");
    sqrtBt.height = "40px";
    sqrtBt.onPointerUpObservable.add(function() {
      CGALWrapper.smoothMesh(Smooth_Algorithm.Sqrt);
      const mesh_data = CGALWrapper.getMeshData() as any;
      updateMesh(mesh, {...mesh_data, colors: null});
    });
    stackPanel.addControl(sqrtBt);

    // let decimateBt = Button.CreateSimpleButton("but5", "Decimate");
    // decimateBt.height = "40px";
    // decimateBt.onPointerUpObservable.add(function() {
    //   CGALWrapper.decimateMesh({targetCount: 0.1});
    //   const mesh_data = CGALWrapper.getMeshData() as any;
    //   updateMesh(mesh, {...mesh_data, colors: null});
    // });
    // stackPanel.addControl(decimateBt);
    
  })
});