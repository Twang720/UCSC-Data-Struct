/*
 * Timmy Wang
 * tqwang CS12B
 * DictionaryTest.c
 * Tests functions for Dictionary.c
 */
#include "Dictionary.h"

int main() {
    const int tableSize = 37;	// set to 101 in assignment description

    char *sites[] =  {
	"accuweather.com",
	"alipay.com",
	"amazon.com",
	"baidu.com",
	"bing.com",
	"csdn.net",
	"ebay.com",
	"facebook.com",
	"google.com",
	"google.com.ar",
	"google.com.au",
	"google.com.br",
	"google.ca",
	"google.fr",
	"google.de",
	"google.com.hk",
	"google.co.in",
	"google.co.id",
	"google.it",
	"google.co.jp",
	"google.pl",
	"google.ru",
	"google.es",
	"google.co.th",
	"google.com.tr",
	"google.co.uk",
	"goo.gl",
	"googleweblight.com",
	"360.cn",
	"instagram.com",
	"jd.com",
	"linkedin.com",
	"mail.ru",
	"microsoft.com",
	"office.com",
	"msn.com",
	"Naver.com",
	"netflix.com",
	"ok.ru",
	"reddit.com",
	"samsung.com",
	"sm.cn",
	"sina.com.cn",
	"weibo.com",
	"sogou.com",
	"sohu.com",
	"spotify.com",
	"t.co",
	"taobao.com",
	"qq.com",
	"tmall.com",
	"pages.tmall.com",
	"list.tmall.com",
	"twitch.tv",
	"twitter.com",
	"vk.com",
	"whatsapp.com",
	"wikipedia.org",
	"live.com",
	"yahoo.com",
	"yahoo.co.jp",
	"youtube.co"};



    	HashTableObj  *H;
    	int i;

    	// you can make this hash table size anything you like that is a prime but the example
    	// results will be different based on the has table size.
    	H = newHashTable(tableSize);

    	for (i=0; i< 62; i++) {
        	insert(H, sites[i]);
    	}
	printHashTable(stdout, H);	

	// test member function
	if(member(H, "wikipedia.org")==true)
		printf("found wikipedia.org\n");
	else
		printf("something wrong with member\n");
	if(member(H, "asktimmy.com")==false)
		printf("didn't find asktimmy.com, good\n");
	else
		printf("found something that didn't get inserted\n");
	printf("deleting and making new hash tree\n");
	deleteHashTable(H);
	printf("new hash table of size 1\n");
	H = newHashTable(1);
	printf("insert a str\n");
	insert(H, "hey");
	printHashTable(stdout, H);
	if(delete(H, "hey")==true)
		printf("success delete\n");
	else
		printf("something went wrong\n");
	printf("delete again\n");
	if(delete(H, "hey")==false)
		printf("success no delete\n");
	else
		printf("something went wrong\n");
	
	
	printf("done\n");
	return 0;
}
