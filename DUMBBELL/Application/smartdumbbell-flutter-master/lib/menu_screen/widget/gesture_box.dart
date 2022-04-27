import 'package:flutter/material.dart';
import '../../constants.dart';

class GestureBox extends StatelessWidget {
  final dynamic gesture;
  final dynamic reps;
  final dynamic setOfrep;
  final bool status;
  final bool active;
  const GestureBox(
      {Key? key,
      this.gesture,
      this.reps,
      this.setOfrep,
      required this.status,
      this.active = false})
      : super(key: key);

  @override
  Widget build(BuildContext context) {
    String titleGesture = "Dumbbell Bicep Curls";
    String imageGesture = "bicep_curls.gif";

    switch (gesture) {
      case 1:
        titleGesture = "Dumbbell Bicep Curls";
        imageGesture = "bicep_curls.gif";
        break;
      case 2:
        titleGesture = "Dumbbell Front Raises";
        imageGesture = "front_raises.gif";
        break;
      case 3:
        titleGesture = "Dumbbell Bent Over Row";
        imageGesture = "bent_over_row.gif";
        break;
      case 4:
        titleGesture = "Dumbbell Cuban Press";
        imageGesture = "cuban_press.gif";
        break;
      case 5:
        titleGesture = "Dumbbell Fly";
        imageGesture = "fly.gif";
        break;
    }
    return InkWell(
      child: Container(
          decoration: BoxDecoration(
              border: Border.all(width: 0.3, color: gestureBoxBorderColor),
              color: Colors.white,
              borderRadius: BorderRadius.circular(22),
              boxShadow: const [
                BoxShadow(
                    color: gestureBoxShadowColor,
                    offset: Offset(0, 1),
                    blurStyle: BlurStyle.normal,
                    spreadRadius: 1)
              ]),
          child: Row(
            children: [
              Container(
                  padding: const EdgeInsets.fromLTRB(10, 10, 0, 10),
                  child: Image.asset('assets/gesture/$imageGesture',
                      height: 70, fit: BoxFit.fill)),
              Column(
                  mainAxisAlignment: MainAxisAlignment.start,
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      '$reps REPS $setOfrep SET',
                      style: const TextStyle(
                          fontWeight: FontWeight.bold, color: Colors.black),
                      textAlign: TextAlign.left,
                    ),
                    Text(titleGesture,
                        textAlign: TextAlign.left,
                        style: const TextStyle(color: gestureBoxTitleColor))
                  ]),
              (status) ? const Text('55') : const Text('55')
            ],
          )),
      onTap: () {
        print("Click event on Container");
      },
    );
  }
}
