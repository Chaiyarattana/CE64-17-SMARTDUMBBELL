import 'package:flutter/material.dart';
import 'widget/gesture_box.dart';
import 'widget/days_box.dart';
import 'start_screen.dart';
import 'edit_gesture_screen.dart';
import 'package:flutter_blue/flutter_blue.dart';

class MenuScreen extends StatefulWidget {
  const MenuScreen({Key? key}) : super(key: key);

  @override
  State<MenuScreen> createState() => _MenuScreenState();
}

class _MenuScreenState extends State<MenuScreen> {
  @override
  Widget build(BuildContext context) {
    print(context);
    return Container(
      padding: const EdgeInsets.fromLTRB(30, 10, 30, 10),
      child: Column(
        children: [
          const DaysBox(),
          SizedBox(
            child: ListView.separated(
              separatorBuilder: (context, index) => const SizedBox(
                height: 15,
              ),
              shrinkWrap: true,
              itemCount: 4,
              itemBuilder: (context, index) => GestureDetector(
                  onTap: () {
                    print("44");
                  },
                  child: Container(
                      padding: const EdgeInsets.all(0),
                      child: const GestureBox(
                          gesture: 2, reps: 10, setOfrep: 5, status: true))),
            ),
          ),
          Container(
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(20),
                color: Colors.blue,
              ),
              width: MediaQuery.of(context).size.width * 0.6,
              margin: const EdgeInsets.only(top: 40),
              child: TextButton(
                onPressed: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(
                        builder: (context) => const StartScreen()),
                  );
                },
                child: const Text("Let\' Start",
                    style: TextStyle(color: Colors.white)),
              ))
        ],
      ),
    );
  }
}
