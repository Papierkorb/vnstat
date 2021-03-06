#include "common.h"
#include "dbxml.h"

void showxml(void)
{
	int i;

	printf(" <interface id=\"%s\">\n", data.interface);

	printf("  <id>%s</id>\n", data.interface);
	printf("  <nick>%s</nick>\n", data.nick);

	printf("  <created>");
	xmldate(&data.created, 1);
	printf("</created>\n");
	printf("  <updated>");
	xmldate(&data.lastupdated, 2);
	printf("</updated>\n");

	printf("  <traffic>\n");
	printf("   <total><rx>%"PRIu64"</rx><tx>%"PRIu64"</tx></total>\n", (data.totalrx*1024)+data.totalrxk, (data.totaltx*1024)+data.totaltxk);

	printf("   <days>\n");
	for (i=0;i<=29;i++) {
		if (data.day[i].used) {
			printf("    <day id=\"%d\">", i);
			xmldate(&data.day[i].date, 1);
			printf("<rx>%"PRIu64"</rx><tx>%"PRIu64"</tx></day>\n", (data.day[i].rx*1024)+data.day[i].rxk, (data.day[i].tx*1024)+data.day[i].txk);
		}
	}
	printf("   </days>\n");

	printf("   <months>\n");
	for (i=0;i<=11;i++) {
		if (data.month[i].used) {
			printf("    <month id=\"%d\">", i);
			xmldate(&data.month[i].month, 3);
			printf("<rx>%"PRIu64"</rx><tx>%"PRIu64"</tx></month>\n", (data.month[i].rx*1024)+data.month[i].rxk, (data.month[i].tx*1024)+data.month[i].txk);
		}
	}
	printf("   </months>\n");

	printf("   <tops>\n");
	for (i=0;i<=9;i++) {
		if (data.top10[i].used) {
			printf("    <top id=\"%d\">", i);
			xmldate(&data.top10[i].date, 2);
			printf("<rx>%"PRIu64"</rx><tx>%"PRIu64"</tx></top>\n", (data.top10[i].rx*1024)+data.top10[i].rxk, (data.top10[i].tx*1024)+data.top10[i].txk);
		}
	}
	printf("   </tops>\n");

	printf("   <hours>\n");
	for (i=0;i<=23;i++) {
		if (data.hour[i].date!=0) {
			printf("    <hour id=\"%d\">", i);
			xmldate(&data.hour[i].date, 1);
			printf("<rx>%"PRIu64"</rx><tx>%"PRIu64"</tx></hour>\n", data.hour[i].rx, data.hour[i].tx);
		}
	}
	printf("   </hours>\n");

	printf("  </traffic>\n");
	printf(" </interface>\n");

}

void xmldate(time_t *date, int type)
{
	struct tm *d;
	char *type1 = "<date><year>%d</year><month>%02d</month><day>%02d</day></date>";
	char *type2 = "<date><year>%d</year><month>%02d</month><day>%02d</day></date><time><hour>%02d</hour><minute>%02d</minute></time>";
	char *type3 = "<date><year>%d</year><month>%02d</month></date>";

	d = localtime(date);

	if (type == 1) {
		printf(type1, 1900+d->tm_year, 1+d->tm_mon, d->tm_mday);
	} else if (type == 2) {
		printf(type2, 1900+d->tm_year, 1+d->tm_mon, d->tm_mday, d->tm_hour, d->tm_min);
	} else if (type == 3) {
		printf(type3, 1900+d->tm_year, 1+d->tm_mon);
	}
}

void xmlheader(void)
{
	printf("<vnstat version=\"%s\" xmlversion=\"%d\">\n", VNSTATVERSION, XMLVERSION);
}

void xmlfooter(void)
{
	printf("</vnstat>\n");
}
