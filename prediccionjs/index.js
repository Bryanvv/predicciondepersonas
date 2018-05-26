var brain = require('brainjs');
var SerialPort = require('serialport');

var port = new SerialPort('/dev/COM5', {
  baudRate: 9600

});


var Sensor1 = 0;
var Sensor1Tmp = 0;
var Estado = 0;
var Sensor2 = 0;
var Sensor2Tmp = 0;
//arreglo de 100
const Neurona = new brain.NeuralNetwork();

Neurona.train([{
    input: {
      Sensor1: 1,
      Sensor2: 1
    },
    output: {
      Ninguna: 1,
      Unapersona: 0,
      Dospersonas: 0
    }
  },
  {
    input: {
      Sensor1: 0.2,
      Sensor2: 1
    },
    output: {
      Ninguna: 0,
      Unapersona: 1,
      Dospersonas: 0
    }
  },
  {
    input: {
      Sensor1: 1,
      Sensor2: 0.2
    },
    output: {
      Ninguna: 0,
      Unapersona: 1,
      Dospersonas: 0
    }
  },
  {
    input: {
      Sensor1: 0.2,
      Sensor2: 0.2
    },
    output: {
      Ninguna: 0,
      Unapersona: 0,
      Dospersonas: 1
    }
  }
]);


port.on('data', function(data) {
  for (var i = 0; i < data.length; i++) {
    switch (Estado) {
      case 0:
        if (data[i] == 97) {
          Estado = 1;
          Sensor1Tmp = 0;
        } else if (data[i] == 100) {
          Estado = 2;
          Sensor2Tmp = 0;
        }
        break;
      case 1:
        if (data[i] == 99) {
          Sensor1 = Sensor1Tmp;
          Estado = 0;
          //console.log("El Valor es:" + Sensor1);
        } else {
          Sensor1Tmp = Sensor1Tmp * 10 + data[i];
        }
        break;
      case 2:
        if (data[i] == 101) {
          Sensor2 = Sensor2Tmp;
          Estado = 0;
          var respuesta = Neurona.run([Sensor1/300, Sensor2/300]);
          if (respuesta.Ninguna > 1) {
            console.log("No hay nadie");
          } else if (respuesta.Unapersona > 0.1) {
            console.log("Hay una persona");
          } else if (respuesta.dospersona > 0.1) {
            console.log("Hay dos personas");
          } else {
            console.log("No se que decis");
          }
          console.log("Valor 1 " + Sensor1 + " Valor 2 " + Sensor2);

        } else {
          Sensor2Tmp = Sensor2Tmp * 10 + data[i];
        }
        break;
    }
  }
});
