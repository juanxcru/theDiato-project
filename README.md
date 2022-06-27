<h1>Introduccion</h1>
<p align="justify">A partir de un instrumento electrónico nacido entre 1920 y 1930, el theremin nace el proyecto del <b>TheDiato</b>. El theremin básicamente es un generador de onda que varía su frecuencia (altura) y amplitud (volumen), a partir de la variación del campo magnético, generado por dos antenas (horizontal y vertical).  Entonces, introduciendo una parte del cuerpo, como la mano, funcionando ésta cómo un capacitor, varia la frecuencia del campo.</p>
<p align="justify">El theremin varía su frecuencia en valores continuos, por lo que hace un poco ardua la tarea de tocar junto a otros instrumentos en un sistema tonal. 
TheDiato adapta la manera de tocar del theremin a otra tecnología, variando discretamente entre valores de frecuencia.
En resumen, <b>TheDiato</b> es un instrumento que se ejecuta acercando y/o alejando la mano del sensor, dándonos una salida directa por PWM y otra por serie (USB y MIDI), pudiendo controlar escalas y octavas.</p>

<h1>Funcionamiento</h1>
<p align="justify">La base de funcionamiento del <b>TheDiato</b> viene a partir de la distancia que hay entre el sensor del instrumento y la mano de la persona ejecutante: mientras más lejos del sensor se ponga la mano, más aguda será la nota. El sensor, es un sensor ultrasónico (módulo HC SR 04) que emite una onda sonora de ultra frecuencia, cuando se le ordena hacerlo, y al encontrarse con un obstáculo, la onda rebota y es recibida por el sensor, devolviendo en uno de sus pines un pulso de ancho igual al tiempo que tardo en ir y volver. De acá se puede calcular la distancia recorrida. (Distancia = Velocidad (sonido en aire)/ Tiempo .</p>
<p align="justify">El sensor es controlado y leído por una placa Arduino, que según la distancia que haya calculado, emite una frecuencia en una salida PWM. Además, envía por comunicación serie datos de la nota de manera MIDI, pudiendo conectar directamente a una PC por USB, (generando un puerto virtual MIDI) haciendo sonar un VST, y/o por cable MIDI a un sintetizador: en otras palabras, usando TheDiato como controlador.</p>
<p align="justify">Las notas que TheDiato emite, están acotadas a las ocho notas de una escala mayor, es decir, si por ejemplo se toca en DO MAYOR, las notas serian DO – RE – MI- FA – SOL – LA- SI – DO, discretamente (una nota, u otra). Con el botón de escala se elige que escala mayor tocar a partir de la escala de DO (DO RE MI FA SOL LA SI). </p>
<p align="justify">Además, hay dos botones de octava, uno que sube una octava y otro que baja una octava. Por default empieza en la octava 4 de un piano, se puede bajar dos octavas, o subir tres (tomando la octava 4 como centro). La duración de nota está atado a un valor de tiempo específico en milisegundos.</p>

<p align="justify">La programación del Arduino se hizo con el software Arduino IDE, sobre una placa Arduino MEGA (podría ser cualquier plataforma similar, o simplemente un microcontrolador que reúna las características necesarias) el sensor es un módulo (no solo los transductores) HC SR 04. Se hicieron pruebas en protoboard y luego se diseñaron dos placas en Proteus, una para control de octava, control de escala y encendido y otra para el sensor.</p>


<p align="center">
  <img src="https://user-images.githubusercontent.com/67986196/176058811-e3d1c0f9-7bcd-4bc1-9071-00dfa5c37000.png" />
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/67986196/176058919-3a1be704-534b-4233-9ed0-dec0694a074e.png" />
</p>


<p align="justify">Las notas se envían con velocidad 100 junto con el CC de portamento activado, en el CH 1. Luego de un tiempo, se envía el note on con velocidad 0 para terminar la nota. En el caso de enviar por USB, para poder leerlo como MIDI en un VST, se puede usar un programa como Loop MIDI, que genera un puerto virtual de MIDI desde el puerto serie de la pc (USB), y otro software para que traduzca de usb a MIDI propiamente (Hairless MIDISERIAL).

<p align="center">
  <img src="https://user-images.githubusercontent.com/67986196/176055479-6f402901-5d23-4410-8249-01750d4417b0.png" />
  <img src="https://user-images.githubusercontent.com/67986196/176055379-1111c19e-41c3-4bdd-80a2-d82c6f484108.png" />
</p>
<p align="center">
  <img src="https://user-images.githubusercontent.com/67986196/176055379-1111c19e-41c3-4bdd-80a2-d82c6f484108.png" />
</p>

