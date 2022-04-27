import 'package:flutter/material.dart';

class DaysBox extends StatefulWidget {
  const DaysBox({Key? key}) : super(key: key);

  @override
  State<DaysBox> createState() => _DaysBoxState();
}

class _DaysBoxState extends State<DaysBox> {
  final now = DateTime.now();
  final daysList = ['Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat', 'Sun'];
  int _selectedIndex = DateTime.now().weekday - 1;

  @override
  Widget build(BuildContext context) {
    return Container(
        margin: const EdgeInsets.only(bottom: 10, top: 10),
        height: 30,
        child: ListView(scrollDirection: Axis.horizontal, children: [
          Container(
            decoration: (0 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
                onPressed: () {
                  setState(() {
                    _selectedIndex = 0;
                  });
                },
                child: Text(
                  daysList[0],
                  style: TextStyle(
                      color:
                          (0 == _selectedIndex) ? Colors.white : Colors.blue),
                )),
          ),
          Container(
            decoration: (1 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
              onPressed: () {
                setState(() {
                  _selectedIndex = 1;
                });
              },
              child: Text(daysList[1],
                  style: TextStyle(
                      color:
                          (1 == _selectedIndex) ? Colors.white : Colors.blue)),
            ),
          ),
          Container(
            decoration: (2 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
              onPressed: () {
                setState(() {
                  _selectedIndex = 2;
                });
              },
              child: Text(daysList[2],
                  style: TextStyle(
                      color:
                          (2 == _selectedIndex) ? Colors.white : Colors.blue)),
            ),
          ),
          Container(
            decoration: (3 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
              onPressed: () {
                setState(() {
                  _selectedIndex = 3;
                });
              },
              child: Text(daysList[3],
                  style: TextStyle(
                      color:
                          (3 == _selectedIndex) ? Colors.white : Colors.blue)),
            ),
          ),
          Container(
            decoration: (4 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
              onPressed: () {
                setState(() {
                  _selectedIndex = 4;
                });
              },
              child: Text(daysList[4],
                  style: TextStyle(
                      color:
                          (4 == _selectedIndex) ? Colors.white : Colors.blue)),
            ),
          ),
          Container(
            decoration: (5 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
              onPressed: () {
                setState(() {
                  _selectedIndex = 5;
                });
              },
              child: Text(daysList[5],
                  style: TextStyle(
                      color:
                          (5 == _selectedIndex) ? Colors.white : Colors.blue)),
            ),
          ),
          Container(
            decoration: (6 == _selectedIndex)
                ? BoxDecoration(
                    borderRadius: BorderRadius.circular(12),
                    color: Colors.blue,
                  )
                : null,
            child: TextButton(
              onPressed: () {
                setState(() {
                  _selectedIndex = 6;
                });
              },
              child: Text(daysList[6],
                  style: TextStyle(
                      color:
                          (6 == _selectedIndex) ? Colors.white : Colors.blue)),
            ),
          )
        ]));
  }
}
