!*********************************************************************
! Filename:      vtop1.f
! Author:        Vijay Sonnad
! Created at:    Mon Nov 16 15:01:44 2009
! Modified at:   Thu Nov 19 13:33:16 2009
! Modified by:   Eddie Baron <baron@ou.edu>
! Version:       
! Description:   
!*********************************************************************
!--
!-- This code 
!-- uses MPI virtual topology routines
!--
!--
!--
!-- MPI_CART_CREATE
!-- MPI_CARTDIM_GET
!-- MPI_CART_GET
!-- MPI_CART_SHIFT
!--
!--
!--
!--
!--
      program vtop1
      implicit none
      include "mpif.h"
      integer, parameter :: sp=kind(0.),dp=kind(0.d0)
      integer :: myrank,nprocs,error
      integer :: source,dest,count,tag,root
      integer :: MESH_1D
      integer :: rank,coord,dim,npdim
      integer :: lplace,rplace,ldest,rdest
      integer :: status(MPI_STATUS_SIZE)
      integer :: i
      logical :: period,reorder
!
      ! mpi_init:
      ! Starts up the MPI environment. MPI calls may now be performed.
      call mpi_init(error)

      ! mpi_comm_size:
      ! Sets the total number of processes for the MPI job to `nprocs`. This
      !   is the number of processes in MPI_COMM_WORLD (by specification as an
      !   argument), which is the default MPI communicator (group of processes).
      call mpi_comm_size(MPI_COMM_WORLD,nprocs,error)

      ! mpi_comm_rank:
      ! Sets the rank (ID) of the individual process from MPI_COMM_WORLD to
      !   `myrank`.
      call mpi_comm_rank(MPI_COMM_WORLD,myrank,error)

      if(nprocs .ne. 4) then
       if(myrank .eq. 0) write(*,*)"Error: Nprocs .ne. 4"

       ! mpi_finalize:
       ! Cleans up and ends the MPI environment.
       call mpi_finalize(error)
       stop "Nprocs .ne. 4"
      endif

!--
!-- Define a linear non periodic arrary
!--
      period = .false.
      reorder = .false.
      dim = 1

      ! mpi_cart_create:
      ! Sets the handle to a new Cartesian topology based on MPI_COMM_WORLD to
      !   `MESH_1D`. The Cartesian topology is of dimension `dim` and the number
      !   of processes in each dimension is `nprocs` in this case. `period`
      !   decides whether each dimension is periodic, and `reorder` decides
      !   whether the rank of each new process in the new topology is the same
      !   as (.false.) or reordered from (.true.) the old group.
      call mpi_cart_create(MPI_COMM_WORLD,dim,nprocs,
     &   period,reorder,MESH_1D,error)
!--
!-- Query the new communicator
!--
      ! mpi_cartdim_get:
      ! Sets the dimension of the communicator `MESH_1D` to `dim`.
      call mpi_cartdim_get(MESH_1D,dim,error)
      write(*,*)"Number of dimensions = ",dim

      ! mpi_cart_get:
      ! Gets topological information from `MESH_1D` with dimension `dim`, i.e
      !   the number of processes in each dimension (`npdim`), the periodicity
      !   (.true./.false. -> `period`) of each dimension, and the Cartesian
      !   coordinate of the individual process running (`coord`).
      call mpi_cart_get(MESH_1D,dim,npdim,period,coord,error)
      write(*,*)"Number of nodes in this dimension =",npdim
      write(*,*)"Periodic",period
      write(*,*)"My coordinates =",coord

      ! mpi_cart_rank:
      ! Gets the Cartesian coordinate and rank (ID) from the communicator
      !   `MESH_1D`.
      call mpi_cart_rank(MESH_1D,coord,rank,error)
      write(*,*)"My rank in this communicator = ",rank
      write(*,*)"My coordinates in this linear array",coord
!--
!-- Determine right and left neighbors
!--
      ! mpi_cart_shift:
      ! "Shift" to some neighboring process of this process. The first non-comm
      !   argument is the direction that the neighbor is in, and the next
      !   argument is the displacement. It then gets the rank of both this
      !   process (--> `rank`) and the neighbor process (--> `rdest`/`ldest`).
      call mpi_cart_shift(MESH_1D,0,1,rank,rdest,error)
      write(*,*)"right neighbor",rdest
      call mpi_cart_shift(MESH_1D,0,-1,rank,ldest,error)
      write(*,*)"left neighbor",ldest
!--
!-- send/recv between neighbors
!--
      if(mod(myrank,2) .eq. 0) then
       if(myrank .ne. nprocs-1) then
        count = 1
        tag = 99
        ! mpi_sendrecv
        ! This function handles both sending and receiving of a source to a
        !   receiver.
        ! This sends a MPI_INTEGER-type message of count 1 from this process
        !   (the one with `myrank`) to the right neighbor (using `rdest`). The
        !   address of the message received is given to `rplace`, and is sent
        !   with tag `tag`.
        ! The number of elements in the received message is given by `count`,
        !   and the type of the elements received is again MPI_INTEGER in this
        !   case. The rank of the receiver is again given with `rdest`, and then
        !   the tag (`tag`) is given to specify that the send/receive message
        !   share the same tag. This all happens on the topological communicator
        !   MESH_1D. The status `status` is also updated.
        call mpi_sendrecv(myrank,1,MPI_INTEGER,rdest,tag,
     &     rplace,count,MPI_INTEGER,rdest,tag,MESH_1D,status,error)
       endif
       if(myrank .ne. 0) then
        count = 1
        tag = 100
        write(*,*)"Myrank ",myrank,"place1"
        ! Similar to the above.
        call mpi_sendrecv(myrank,count,MPI_INTEGER,ldest,tag,
     &     lplace,count,MPI_INTEGER,ldest,tag,MESH_1D,status,error)
       endif
!
       write(*,*)"after exchange (lplace,rplace)",lplace,rplace
      endif
      if(mod(myrank,2) .ne. 0) then
       if(myrank .ne. 0) then
        count = 1
        tag = 99
        ! Similar to the above.
        call mpi_sendrecv(myrank,1,MPI_INTEGER,ldest,tag,
     &     lplace,count,MPI_INTEGER,ldest,tag,MESH_1D,status,error)
       endif
       if(myrank .ne. nprocs-1) then
        count = 1
        tag = 100
        write(*,*)"Myrank ",myrank,"place3"
        ! Similar to the above.
        call mpi_sendrecv(myrank,count,MPI_INTEGER,rdest,tag,
     &     rplace,count,MPI_INTEGER,rdest,tag,MESH_1D,status,error)
       endif
       write(*,*)"after exchange (lplace,rplace)",lplace,rplace
      endif

!
      ! mpi_finalize:
      ! Cleans up and ends the MPI environment.
      call mpi_finalize(error)
      stop
      end
