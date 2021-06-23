<?php

namespace App\Entity;

use App\Repository\DataRepository;
use Doctrine\ORM\Mapping as ORM;

/**
 * @ORM\Entity(repositoryClass=DataRepository::class)
 */
class Data
{
    /**
     * @ORM\Id
     * @ORM\GeneratedValue
     * @ORM\Column(type="integer")
     */
    private $id;

    /**
     * @ORM\Column(type="integer")
     */
    private $id_data;

    /**
     * @ORM\Column(type="date")
     */
    private $date;

    /**
     * @ORM\Column(type="integer")
     */
    private $temperature;

    /**
     * @ORM\Column(type="integer")
     */
    private $gaz;

    /**
     * @ORM\Column(type="string", length=255, nullable=true)
     */
    private $video;

    /**
     * @ORM\Column(type="boolean")
     */
    private $incident;

    public function getId(): ?int
    {
        return $this->id;
    }

    public function getIdData(): ?int
    {
        return $this->id_data;
    }

    public function setIdData(int $id_data): self
    {
        $this->id_data = $id_data;

        return $this;
    }

    public function getDate(): ?\DateTimeInterface
    {
        return $this->date;
    }

    public function setDate(\DateTimeInterface $date): self
    {
        $this->date = $date;

        return $this;
    }

    public function getTemperature(): ?int
    {
        return $this->temperature;
    }

    public function setTemperature(int $temperature): self
    {
        $this->temperature = $temperature;

        return $this;
    }

    public function getGaz(): ?int
    {
        return $this->gaz;
    }

    public function setGaz(int $gaz): self
    {
        $this->gaz = $gaz;

        return $this;
    }

    public function getVideo(): ?string
    {
        return $this->video;
    }

    public function setVideo(?string $video): self
    {
        $this->video = $video;

        return $this;
    }

    public function getIncident(): ?bool
    {
        return $this->incident;
    }

    public function setIncident(bool $incident): self
    {
        $this->incident = $incident;

        return $this;
    }
}
