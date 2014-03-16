//(
//Server.default = s = Server.internal.boot;
SynthDef("perc", {
	arg amp=0.02, pan = 0.0, freq=440, detune=2.0, decay=0.1;
	var env, out;
	out = Pan2.ar(SinOsc.ar(freq), pan);
	env = EnvGen.kr(Env.perc(0.001,decay,1,-4), doneAction: 2);
	out = out * env * amp;
	Out.ar(0, out);
}).store;

SynthDef(\test, { | out, freq = 440, amp = 0.1, nharms = 10, pan = 0, gate = 1 |
    var audio = Blip.ar(freq, nharms, amp);
    var env = Linen.kr(gate, doneAction: 2);
    OffsetOut.ar(out, Pan2.ar(audio, pan, env) );
}).store;
(


var fib, bass, mel, ending,tune,x0, y0, x, y;
//n = NetAddr.new("192.168.0.101", 12345);    // create the NetAddr
fib = #[60, 62, 63, 65, 68, 73];

bass = Pbind(
 \instrument, \test,
 \tempo, 1.5,
 \legato, 0.01,
 \dur, Pseq([1], 5),
 \midinote, Pxrand(fib - 24, 5)

);
mel = Pbind(
//\instrument, \sine,
 \tempo, 1.5,
 \legato, Prand([1,1,1/2,1/3, 1/5, 1/8], inf),
 \dur, Pshuf([1,1,Pseq([1/2],2),Pseq([1/3],3), Pseq([1/3], 3)], 1),
 \midinote, Prand( fib ++ [\rest, \rest] , 10)
);

tune = Pseq([
   Ppar([ bass, mel, mel ],2),
   Padd(\ctranspose, 7,  Ppar([ bass, mel, mel ],2)),
   Padd(\ctranspose, -7, Ppar([ bass, mel, mel ],2))
  ], inf);

tune.play;



///modificata con uno strumento \test

//var x0, y0, x, y;


p = Prout({

	x0=0; y0=0;
	loop({


		x = y0 + 1 - (1.4*x0*x0);

		y = 0.3*x0;

		x0=x;y0=y;

		[x, y*14].postln.yield;

//n.sendMsg("/servo/position1", x);
//n.sendMsg("/servo/position2", y);
	});
});

// cambia /dur per cambiare il tempo (durata)
b = Pbind(\instrument, \perc, \scale, [0,2,3,5,7,9,10], \dur,1.225,\db,0.8,[\pan, \degree], p );



Ptpar([0.0,Pbindf(b, \octave, 4,\stretch, 3.0), 4.0,b]).play;
)
//)
