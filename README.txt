David Ulriksen
002270761

I worked alone in this submission.

I am also including what i have done on the red black tree. I worked on it far more than i should have,
because i only got it to the point where it detects it needs one color switch/rotation, but not more. 
I was able to make it match up to the red black visualizer for quite a long ways. But i guess dead is better than red...


And before we go further, please take this as a plea of mercy. Not for how the program is to be judged,
but on the fact that i was committed to this project and worked it like a job, for over 50 hours this week.
I worked on this constantly. no games. no tv. no friends. no family. no thanksgiving. And i am horribly disappointed with how it game out.

=========================================================================
How the rollback is SUPPOSED to work:

The rollback I have created is supposed to work by
creating a file for each step. 

Firstly, it shifts all history record file names,
making room for a new file at the start.

Secondly, it renames the current database to be the first history record.

Third, the action is performed and saved into the main database.

Fourth, the program is restarted, it resumes with the data from the main table. History is discarded upon restart.
=========================================================================



PROGRAM NOTES:
1. There is currently a bug i have been struggling to squash.
Literal struggling. This bug, if its even one bug, effects
several of the bottom most prompts. 

2. This bug effects half of rollback, and segfaults for SOME GOD DAMN REASON I CAN'T find.
Every part works except bringing the data back from the previous step for the STUDENTS.
it works fine for teachers. It just hates students apparently. 

3. This bug also effects how students are handled with regards to their relationships to the faculty.
Sometimes, the amount of students that a faculty member advises is incremented by 4. This happens usually
when the program restarts. The order of the suddenly appearing bunch of students is the exact opposite 
of the first four (when the bug first occurs).

4. Just to clarify how this bug effects changing an advisor/removing an advisee...
The commands WORK! but because there are somehow duplicate students occasionally being added in....
the professor maintains a connection to that student, despite the original being deleted.
Changing the advisor of a student works, the old professor just still has a duplicate name.
Removing an advisor from a faculty member works, but once. 
The faculty member might still still be shitting out more god damn duplicate students by that time.

===========================================================================




References:
Jamie Newbon - a professional developer who helped me get into visual studio and start using some better techniques and methods in coding.
https://stackoverflow.com/questions/1691007/whats-the-right-way-to-overload-operator-for-a-class-hierarchy
https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
http://software.ucv.ro/~mburicea/lab8ASD.pdf
http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
