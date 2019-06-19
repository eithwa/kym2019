//===================================================================
// HSV 
var ParameterHSV_Red = new ROSLIB.Param({
    ros: ros,
    name: '/tb3/HSV/Red',
});
var ParameterHSV_Blue = new ROSLIB.Param({
    ros: ros,
    name: '/tb3/HSV/Blue',
});
var ParameterHSV_Yellow = new ROSLIB.Param({
    ros: ros,
    name: '/tb3/HSV/Yellow',
});
var ParameterHSV_White = new ROSLIB.Param({
    ros: ros,
    name: '/tb3/HSV/White',
});
var ParameterHSV_Black = new ROSLIB.Param({
    ros: ros,
    name: '/tb3/HSV/Black',
});

function Save_HSV() {

    var mode = parseInt(document.getElementById('HSVSelect').value);
    var box = [];
    switch (mode) {
        case 0:
            for (var i = 0; i < 6; i++) {
                box[i] = parseInt(document.getElementsByName('HSVElement')[i].value);
                RedBox[i] = box[i];
            }
            if (Param_HSV_Flag)
                console.log('Param Redbox ' + box);
            //ParameterHSV_Red.set(box);
            break;
        case 1:
            for (var i = 0; i < 6; i++) {
                box[i] = parseInt(document.getElementsByName('HSVElement')[i].value);
                BlueBox[i] = box[i];
            }
            if (Param_HSV_Flag)
                console.log('Param Bluebox ' + box);
            //ParameterHSV_Blue.set(box);
            break;
        case 2:
            for (var i = 0; i < 6; i++) {
                box[i] = parseInt(document.getElementsByName('HSVElement')[i].value);
                YellowBox[i] = box[i];
            }
            if (Param_HSV_Flag)
                console.log('Param Yellowbox ' + box);
            //ParameterHSV_Yellow.set(box);
            break;
        case 3:
            for (var i = 0; i < 6; i++) {
                box[i] = parseInt(document.getElementsByName('HSVElement')[i].value);
                WhiteBox[i] = box[i];
            }
            if (Param_HSV_Flag)
                console.log('Param Whitebox ' + box);
            //ParameterHSV_White.set(box);
            break;
        case 4:
            for (var i = 0; i < 6; i++) {
                box[i] = parseInt(document.getElementsByName('HSVElement')[i].value);
                BlackBox[i] = box[i];
            }
            if (Param_HSV_Flag)
                console.log('Param Blackbox' + box);
            //ParameterHSV_Black.set(box);
            break;
    }
//======================
    if(Param_HSV_Flag){
        ParameterHSV_Red.set(RedBox);
        ParameterHSV_Blue.set(BlueBox);
        ParameterHSV_Yellow.set(YellowBox);
        ParameterHSV_White.set(WhiteBox);
        ParameterHSV_Black.set(BlackBox);  
    }
    setTimeout(Pub_Save(),3000);
    setTimeout(savecall(),3000);
	
}


ParameterHSV_Red.get(function(value) {
    var obj = document.getElementsByName("HSVElement");
    if (value != null) {
        for (var i = 0; i < obj.length; i++) {
            //obj[i].value = value[i];
            RedBox[i] = value[i];
            obj[i].value = value[i];
            document.getElementsByName('HSVLabelElement')[i].innerText = value[i];
        }
    } else {
        for (var i = 0; i < RedBox.length; i++) {
            obj[i].value = RedBox[i];
            document.getElementsByName('HSVLabelElement')[i].innerText = RedBox[i];
        }
    }
});

ParameterHSV_Blue.get(function(value) {
    if (value != null) {
        for (var i = 0; i < value.length; i++) {
            BlueBox[i] = value[i];
        }
    }
});

ParameterHSV_Yellow.get(function(value) {
    if (value != null) {
        for (var i = 0; i < value.length; i++) {
            YellowBox[i] = value[i];
        }
    }
});

ParameterHSV_White.get(function(value) {
    if (value != null) {
        for (var i = 0; i < value.length; i++) {
            WhiteBox[i] = value[i];
        }
    }
});

ParameterHSV_Black.get(function(value) {
    if (value != null) {
        for (var i = 0; i < value.length; i++) {
            BlackBox[i] = value[i];
        }
    }
});

//===================================================================
// vision param 
var Vision_Param = new ROSLIB.Param({
    ros: ros,
    name: '/tb3/center',
});

function Save_VisionParam() {
    document.getElementById('Red_disable').checked = false;
    document.getElementById('Blue_disable').checked = false;
    document.getElementById('Yellow_disable').checked = false;
    document.getElementById('White_disable').checked = false;
    document.getElementById('Black_disable').checked = false;

    var obj = document.getElementsByName('VisionParamElement');
    var box = []
    for (var i = 0; i < obj.length; i++) {
        box[i] = parseInt(obj[i].value);
    }


    if (Param_Vison_Flag)
        console.log('Param Vision ' + box);
    Vision_Param.set(box);
    setTimeout(Pub_Save,1000);
    setTimeout(savecall,1000);
}

Vision_Param.get(function(value) {
    var obj = document.getElementsByName('VisionParamElement');
    var obj2 = document.getElementsByName('VisionParamLabelElement');
    if (value != null) {
        for (var i = 0; i < value.length; i++) {
            obj[i].value = value[i];
            obj2[i].innerText = value[i];
        }
        //document.getElementById("catch_distance_Input").innerText = 123;
        //obj2[4].innerText = value[4];
    } else {
        for (let i = 0; i < VisionParam.length-1; i++) {
            objvar[i].value = VisionParam[i];
            obj2[i].innerText = VisionParam[i];
        }
        //obj2[4].innerText = 0;
    }
});
