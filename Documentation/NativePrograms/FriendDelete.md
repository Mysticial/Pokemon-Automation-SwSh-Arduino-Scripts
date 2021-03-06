# FriendDelete

Delete or block from your friend list.

Once you’ve auto-hosted enough, your friend list is going to fill up. FriendDelete can clean it up.

## Instructions:

Please read these instructions carefully as you can easily delete friends you didn't intend to delete.
1. Mark all the friends you want to keep as "best" friend.
2. Go into Pokémon Sword/Shield. Make sure you're offline.
3. Return to your friends list. All your best friends will be sorted at the top regardless of who's online or not.
4. Scroll all the way to the bottom of your friends list.
5. With the cursor over the last person, start this program. The program will delete your friends one-by-one from the back of the list.
6. Once it has reached your "best" friends, stop the program.

If you know exactly how many friends you wish to delete from the back of your list, you can set the `friends_to_delete` parameter accordingly and it will stop by itself when it's done.

## Required Parameters:
- `friends_to_delete`: You must set this parameter to the # of friends you wish to delete. Otherwise, you may end up deleting friends you didn't intend to delete.

## Options:

### Number of Friends to Delete/Block:
```
const uint16_t FRIENDS_TO_DELETE    =   3;
```
The number of friends to delete or block.

### Block Instead of Delete:
```
const bool BLOCK_FRIENDS            =   false;
```
Set this to true if you want to block these friends instead of just deleting them.

### Internet Connection Delays:
```
//  Delay from opening a friend to when you can press buttons.
const uint16_t VIEW_FRIEND_DELAY    =   2 * TICKS_PER_SECOND;

//  Delay to delete the friend.
const uint16_t DELETE_FRIEND_DELAY  =   8 * TICKS_PER_SECOND;

//  Delay after deleting a friend.
const uint16_t FINISH_DELETE_DELAY  =   2 * TICKS_PER_SECOND;
```
These are all delays related to your internet connection. You may need to adjust these to ensure the program works correctly.

Try with the defaults first. If things don’t work, then try increasing these timings. Likewise, if your internet connection is very fast, feel free to reduce some of these delays.

## Implementation Notes:

There is no way for the program to distinguish "best" friends from regular friends. Therefore you must either tell the program exactly how many to delete, or you must stop it manually.

There is also no way for the program to know when to stop aside from telling it exactly how many friends to delete. When you delete a friend, the cursor automatically moves to the next friend (or the previous if it was your last friend).

Therefore, the only way to feasibly auto-delete friends is to manipulate the sorting order of your friends to group all the ones you want to delete together. Then run the script on that group. Unfortunately, this requires the user to monitor the program while it's running since it's very easy to accidentally delete someone you didn't intend to.

The default sorting order of your friends list is:
1. Best friends who are online.
2. Normal friends who are online.
3. Best friends who are offline.
4. Normal friends who are offline.

However, you can trick it to sort all best friends first by enabling local communication (such as by going offline in Pokémon). This suppresses the online status of your friends when you first load it - thus forcing it to sort only by best friend status. As long as you don't press Y on your friends list or re-enter the friends list while online, it won't re-sort based on online status.




<hr>

**Back to:**
- [Project Home](/README.md)
- [Program List](/Documentation/ProgramList.md)

**Discord Server:** 

[<img src="https://canary.discordapp.com/api/guilds/695809740428673034/widget.png?style=banner2">](https://discord.gg/cQ4gWxN)
