import 'package:flutter/material.dart';
import 'package:flutter_blue/flutter_blue.dart';
import 'package:percent_indicator/circular_percent_indicator.dart';
import '../constants.dart';

import 'dart:async';
import 'dart:math';

class StartScreen extends StatefulWidget {
  const StartScreen({Key? key}) : super(key: key);

  @override
  State<StartScreen> createState() => _StartScreenState();
}

class _StartScreenState extends State<StartScreen> {
  showAlertDialog(BuildContext context) {
    // set up the button
    Widget addTimeButton = ElevatedButton(
      onPressed: () {
        // Respond to button press
      },
      style: ElevatedButton.styleFrom(primary: defaultActionButtonColor),
      child: const Text('+15'),
    );
    Widget skipButton = ElevatedButton(
      onPressed: () {
        // Respond to button press
      },
      child: const Text('SKIP'),
    );
    // set up the AlertDialog
    AlertDialog alert = AlertDialog(
      actionsAlignment: MainAxisAlignment.center,
      title: const Center(child: Text("Break", style: TextStyle(fontSize: 36))),
      content: Column(mainAxisSize: MainAxisSize.min, children: const <Widget>[
        Text("15 s", style: TextStyle(fontSize: 48)),
        Text("Next: Dumbbell Brench Press")
      ]),
      actions: [addTimeButton, skipButton],
    );

    // show the dialog
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return alert;
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('SMART DUMBBELL'),
        centerTitle: false,
        automaticallyImplyLeading: false,
      ),
      body: SingleChildScrollView(
        padding: const EdgeInsets.only(
          top: 25,
        ),
        child: Column(
          children: <Widget>[
            Container(
                padding: const EdgeInsets.fromLTRB(10, 10, 0, 10),
                child: Image.asset('assets/gesture/bench_press.gif',
                    height: MediaQuery.of(context).size.height * 0.15,
                    fit: BoxFit.fill)),
            Column(
              children: <Widget>[
                Padding(
                  padding: const EdgeInsets.only(bottom: 10.0),
                  child: Text(
                    'Dumbbell Brench Press',
                    style: TextStyle(
                      fontSize: 24.0,
                      fontWeight: FontWeight.w900,
                      color: Colors.grey[700],
                    ),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.only(bottom: 15),
                  child: Text(
                    'Next: Dumbbell Bicep Curls', // ชื่อท่าต่อไป
                    style: TextStyle(
                      fontSize: 18.0,
                      fontWeight: FontWeight.w900,
                      color: Colors.grey[300],
                    ),
                  ),
                ),
                Padding(
                  padding: const EdgeInsets.only(top: 20.0),
                  child: CircularPercentIndicator(
                    radius: MediaQuery.of(context).size.width * 0.3, //ขนาดวงกลม
                    animation: true,
                    animationDuration: 1200,
                    lineWidth: 16.0,
                    percent: (0 / 15), //ขนาดเเถบวงกลม
                    center: Text(
                      "0",
                      style: TextStyle(
                        fontSize: 45.0,
                        fontWeight: FontWeight.w900,
                        color: Colors.grey[400],
                      ),
                    ),
                    backgroundColor: Colors.grey,
                    circularStrokeCap: CircularStrokeCap.round,
                    linearGradient: const LinearGradient(
                      colors: [
                        Color.fromRGBO(190, 130, 255, 1.0),
                        Color.fromRGBO(105, 139, 255, 1.0),
                      ],
                    ),
                  ),
                ),
              ],
            ),
            const SizedBox(height: 15),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                Container(
                    width: MediaQuery.of(context).size.width * 0.15,
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(15),
                      color: const Color.fromRGBO(232, 242, 248, 1.0),
                    ),
                    child: IconButton(
                      iconSize: 30,
                      icon: const Icon(Icons.close),
                      color: const Color.fromRGBO(255, 82, 88, 1.0),
                      onPressed: () {
                        Navigator.pop(context);
                      },
                    )),
                // const SizedBox(
                //   width: 5,
                // ),
                // Container(
                //     width: MediaQuery.of(context).size.width * 0.15,
                //     decoration: BoxDecoration(
                //       borderRadius: BorderRadius.circular(15),
                //       color: const Color.fromRGBO(232, 242, 248, 1.0),
                //     ),
                //     child: IconButton(
                //       iconSize: 30,
                //       icon: const Icon(Icons.pause),
                //       color: const Color.fromRGBO(82, 126, 255, 1.0),
                //       onPressed: () {
                //         print(5);
                //       },
                //     )),
                const SizedBox(
                  width: 5,
                ),
                Container(
                    width: MediaQuery.of(context).size.width * 0.4,
                    decoration: BoxDecoration(
                      borderRadius: BorderRadius.circular(15),
                      color: const Color.fromRGBO(232, 242, 248, 1.0),
                    ),
                    child: TextButton.icon(
                      onPressed: () {
                        showAlertDialog(context);
                      },
                      icon: const Icon(Icons.skip_next, size: 30),
                      label: const Text(
                        "Next",
                      ),
                    ))
              ],
            ),
          ],
        ),
      ),
    );
  }
}
