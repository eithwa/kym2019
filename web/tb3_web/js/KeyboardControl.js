window.addEventListener("keydown", keysdown, false);
window.addEventListener("keyup", keyuped, false);

var keys = [];
var start;
var vec3;

function KeyboardState(state) {
    start = state;
}

function keysdown(e) {
    if (start == true) {
        var speed = document.getElementById("SpeedInput").value;
        keys[e.keyCode] = true;

        
        //RobotControl
        //w+d
        if (keys[87] && keys[68]) {
            vec3 = new ROSLIB.Message({
                x: parseFloat(speed/100),
                y: 0,
                z: -parseFloat(speed*2/100)
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "右前";
        } 
        //w+a
        else if (keys[87] && keys[65]) {
            vec3 = new ROSLIB.Message({
                x: parseFloat(speed/100),
                y: 0,
                z: parseFloat(speed*2/100)
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "左前";
        } 
        //s+d
        else if (keys[83] && keys[68]) {
            vec3 = new ROSLIB.Message({
                x: -parseFloat(speed/100),
                y: 0,
                z: -parseFloat(speed*2/100)
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "右後";
        } 
        //s+a
        else if (keys[83] && keys[65]) {
            vec3 = new ROSLIB.Message({
                x: -parseFloat(speed/100),
                y: 0,
                z: parseFloat(speed*2/100)
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "左後";
        } 
        //w
        else if (keys[87]) {
            vec3 = new ROSLIB.Message({
                x: parseFloat(speed/100),
                y: 0,
                z: 0
            });
            PublishTopicCmdVel(vec3);
           // PublishTopicCmdVel(vec3);
           document.getElementById('direction').innerText = "前進";
        } 
        //d
        else if (keys[68]) {
            vec3 = new ROSLIB.Message({
                x: 0,
                y: 0,
                z: -parseFloat(speed*2/100)
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "右轉";
        }
        //s
        else if (keys[83]) {
            vec3 = new ROSLIB.Message({
                x: -parseFloat(speed/100),
                y: 0,
                z: 0
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "後退";
        } 
        //a
        else if (keys[65]) {
            vec3 = new ROSLIB.Message({
                x: 0,
                y: 0,
                z: parseFloat(speed*2/100)
            });
            PublishTopicCmdVel(vec3);
            //PublishTopicCmdVel(vec3);
            document.getElementById('direction').innerText = "左轉";
        }
    }
}

function releasebutton(state) {
    let vec3_ = new ROSLIB.Message({
        x: 0,
        y: 0,
        z: 0
    });
    switch(state){
      case 81:
        vec3.z = 0;
        break;
      case 69:
        vec3.z = 0;
        break;
      case 87:
        vec3.y = 0;
        break;
      case 65:
        vec3.x = 0;
        break;
      case 83:
        vec3.y = 0;
        break;
      case 68:
        vec3.x = 0;
        break;
      default:
        vec3.x = 0;
        vec3.y = 0;
        vec3.Z = 0;
    }
    PublishTopicCmdVel(vec3_);
    document.getElementById('direction').innerText = "停止";
    //PublishTopicCmdVel(vec3);
}

function keyuped(e) {
    if (start) {
        if (keys[e.keyCode] == true) releasebutton(e.keyCode);
        //else if (keys[69] == true) releasebutton(69);
        //else if (keys[87] == true) releasebutton(87);
        //else if (keys[65] == true) releasebutton(65);
        //else if (keys[83] == true) releasebutton(83);
        //else if (keys[68] == true) releasebutton(68);
        keys[e.keyCode] = false;
    }
}
