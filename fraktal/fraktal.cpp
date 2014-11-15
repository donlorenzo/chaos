#include "fraktal.hpp"
  

c_fraktal::c_fraktal( void ) {
	koch_kurve = NULL;
    img = create_bitmap( SCREEN_W, SCREEN_H );
	log_info( "... c_fraktal donstructor DONE\n")	;
}

c_fraktal::~c_fraktal( void ) {
    koch_line* del_item = koch_kurve;
	while( del_item != NULL ) {
	    koch_line *del_it = del_item;
	    del_item = del_item->next;
	    delete( del_it );
	}
	if( img != NULL )
		destroy_bitmap( img );
}    


void c_fraktal::clean_up( void ) {
    koch_line* del_item = koch_kurve;
	while( del_item != NULL ) {
	    koch_line *del_it = del_item;
	    del_item = del_item->next;
	    delete( del_it );
	}    
}

    

BITMAP* c_fraktal::show( void ) {
	clear_bitmap( img );
	int i=0;
	for( koch_line* cur_line = koch_kurve; cur_line != NULL; cur_line = cur_line->next ) {
	    line( img, (int)cur_line->pos.startx, (int)cur_line->pos.starty, (int)cur_line->pos.endx, (int)cur_line->pos.endy, 15 );
	    i++;
	}    
	log_info( "%d elements\n", i+1 );
    return img;
}

int c_fraktal::how_many( void ) {
    int i =0;
    for( koch_line *pos = koch_kurve; pos != NULL; pos = pos->next )
    	i++;
	return i;
}	


/* BACKUP!!!
void c_fraktal::insert( koch_line *koch_kurve ) {
    koch_line* temp;
    koch_line* temp2;
    koch_line* temp3;
    for( koch_line* cur_line = koch_kurve; cur_line != NULL; cur_line = temp2->next->next ) {
    	temp3 = new koch_line;
    	
    	cur_line->length = cur_line->length/3.0f;
    	temp3->length = cur_line->length;
    	temp3->angle = cur_line->angle;
    	temp3->next = cur_line->next;
    	temp3->prev = cur_line->prev;
    	temp3->pos.endx = cur_line->pos.endx;
    	temp3->pos.endy = cur_line->pos.endy;
    	temp3->pos.startx  = cur_line->pos.endx - ( (cur_line->pos.endx - cur_line->pos.startx )/3.0f );
    	temp3->pos.starty  = cur_line->pos.endy - ( (cur_line->pos.endy - cur_line->pos.starty )/3.0f );
    	cur_line->pos.endx = cur_line->pos.startx + ( (cur_line->pos.endx - cur_line->pos.startx )/3.0f );
    	cur_line->pos.endy = cur_line->pos.starty + ( (cur_line->pos.endy - cur_line->pos.starty )/3.0f );

    	
     
     	temp = new koch_line;
    	
    	temp->length = cur_line->length;//sqrt(2.0)*(cur_line->length)/(2.0);
    	temp->angle = cur_line->angle + (120.0f*M_PI)/360.0f;
    	temp->prev = cur_line;
    	temp->next = cur_line->next;
    	cur_line->next = temp;
    	if( temp->next != NULL )
    		temp->next->prev = temp;
		temp->pos.startx = cur_line->pos.endx;
		temp->pos.starty = cur_line->pos.endy;
		temp->pos.endx = temp->pos.startx + temp->length*cos(temp->angle);
		temp->pos.endy = temp->pos.starty - temp->length*sin(temp->angle);

		temp2 = new koch_line;
		temp2->length = temp->length;
		temp2->angle = temp->angle - (240.0f*M_PI)/360.0f;
		temp2->prev = temp;
		temp2->next = temp3;
		temp->next = temp2;
  		temp2->prev->next = temp2;
		if( temp2->next != NULL )
			temp2->next->prev = temp2;
		temp2->pos.startx = temp->pos.endx;
		temp2->pos.starty = temp->pos.endy;
		temp2->pos.endx = temp3->pos.startx;
		temp2->pos.endy = temp3->pos.starty;

    }
}
*/

void c_fraktal::insert( koch_line *koch_kurve ) {
    koch_line* temp;
    koch_line* temp2;
    koch_line* temp3;
    for( koch_line* cur_line = koch_kurve; cur_line != NULL; cur_line = temp2->next->next ) {
    	temp3 = new koch_line;
    	
    	cur_line->length = cur_line->length/3.0f;
    	temp3->length = cur_line->length;
    	temp3->angle = cur_line->angle;
    	temp3->next = cur_line->next;
    	temp3->prev = cur_line->prev;
    	temp3->pos.endx = cur_line->pos.endx;
    	temp3->pos.endy = cur_line->pos.endy;
    	temp3->pos.startx  = cur_line->pos.endx - ( (cur_line->pos.endx - cur_line->pos.startx )/3.0f );
    	temp3->pos.starty  = cur_line->pos.endy - ( (cur_line->pos.endy - cur_line->pos.starty )/3.0f );
    	cur_line->pos.endx = cur_line->pos.startx + ( (cur_line->pos.endx - cur_line->pos.startx )/3.0f );
    	cur_line->pos.endy = cur_line->pos.starty + ( (cur_line->pos.endy - cur_line->pos.starty )/3.0f );

    	
     
     	temp = new koch_line;
    	
    	temp->length = cur_line->length;
    	temp->angle = cur_line->angle + (120.0f*M_PI)/360.0f;
    	temp->prev = cur_line;
    	temp->next = cur_line->next;
    	cur_line->next = temp;
    	if( temp->next != NULL )
    		temp->next->prev = temp;
		temp->pos.startx = cur_line->pos.endx;
		temp->pos.starty = cur_line->pos.endy;
		temp->pos.endx = temp->pos.startx + temp->length*cos(temp->angle);
		temp->pos.endy = temp->pos.starty - temp->length*sin(temp->angle);



		temp2 = new koch_line;

		temp2->length = temp->length;
		temp2->angle = temp->angle - (240.0f*M_PI)/360.0f;
		temp2->prev = temp;
		temp2->next = temp3;
		temp->next = temp2;
  		temp2->prev->next = temp2;
		if( temp2->next != NULL )
			temp2->next->prev = temp2;
		temp2->pos.startx = temp->pos.endx;
		temp2->pos.starty = temp->pos.endy;
		temp2->pos.endx = temp3->pos.startx;
		temp2->pos.endy = temp3->pos.starty;

    }
}

    

void c_fraktal::calculate( int depth ) {
	clean_up();
    int width = SCREEN_W;
    int height = SCREEN_H;
	koch_kurve = new koch_line;
/*//	
	// line
	koch_kurve->length = float(width);
	koch_kurve->angle = 0;
	koch_kurve->next = NULL;
	koch_kurve->prev = NULL;
	koch_kurve->pos.startx = 0;
	koch_kurve->pos.endx = SCREEN_W;
	koch_kurve->pos.starty = koch_kurve->pos.endy = SCREEN_H-10;
//*/

	//triangle
	koch_kurve->length = height/2.0f;
	koch_kurve->angle=0;
	koch_kurve->prev = NULL;
	koch_kurve->pos.startx = SCREEN_W/2.0f - koch_kurve->length/2.0f;
	koch_kurve->pos.endx = SCREEN_W/2.0f + koch_kurve->length/2.0f;
	koch_kurve->pos.starty = koch_kurve->pos.endy = SCREEN_H/2.0f;
	koch_line* temp;
	
 	temp = new koch_line;
	temp->length = koch_kurve->length;
	temp->angle = (480.0*M_PI)/360.0;
	temp->pos.startx = koch_kurve->pos.endx;
	temp->pos.starty = koch_kurve->pos.endy;
	temp->pos.endx = koch_kurve->pos.startx + temp->length/2.0f;
	temp->pos.endy = temp->pos.starty - temp->length*sin(temp->angle);
	temp->prev = koch_kurve;
	koch_kurve->next = temp;

	temp = new koch_line;
	temp->pos.startx = koch_kurve->next->pos.endx;
	temp->pos.starty = koch_kurve->next->pos.endy;
	temp->length = koch_kurve->length;
	temp->angle = (240.0*M_PI)/360.0;
	temp->pos.endx = koch_kurve->pos.startx;
	temp->pos.endy = koch_kurve->pos.starty;
	temp->prev = koch_kurve->next;
	koch_kurve->next->next = temp;
	temp->next = NULL;



	for( int i=0; i<depth; i++ )
		insert( koch_kurve );
	line_cnt = how_many();
}



