// minimal heatmap instance configuration
var heatmapInstance = h337.create({
    // only container is required, the rest will be defaults
    container: document.querySelector('.heatmap')
});
// now generate some random data
var sensor = [];
var max = 100;
var obj;

// Objecten sensoren en locaties
sensor[0] = {
    place: 'Gang gelijkvloers',
    x: 640,
    y: 500,
    value: 0,
    // radius configuration on point basis
    radius: 70
}

sensor[1] = {
    place: 'Gang eerste verdiep',
    x: 340,
    y: 200,
    value: 0,
    // radius configuration on point basis
    radius: 70
}



// heatmap data format
var data = {
    max: max,
    data: sensor
};
// if you have a set of datapoints always use setData instead of addData
// for data initialization
heatmapInstance.setData(data);

function Update()
{
    var sensorData = Refreshdata();

    for(var s in sensorData)
    {
        if (sensorData[s].id == 1)
        {
            sensor[0].value = sensorData[s].sound * 10;
            sensor.push(sensor[0].value);
        }
        else if (sensorData[s].id == 2)
        {
            sensor[1].value = sensorData[s].sound * 10;
            sensor.push(sensor[1].value);
        }
    }

    heatmapInstance.setData(data);
}

setInterval(function () {
        Update();
    }, 500);

function Refreshdata() {
    $.ajax({
        url: "http://192.168.137.144:1880/test",
        dataType: 'jsonp',
        success: function (data) {
            obj = data;
            
        }
    });
    return obj;
}